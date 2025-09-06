#include "ClientDetours.h"
#include "ClientMacros.h"
#include "Util.h"
#include "freetype/freetype.h"
#include "freetype/ftmodapi.h"

typedef void(TEXTURE_CALLBACK)(int, uint32_t, uint32_t, uint32_t, uint32_t, void*, uint32_t&, const void*&);

struct CHARCODEDESC;

struct TSLink_CHARCODEDESC
{
    TSLink_CHARCODEDESC* m_prevLink;
    CHARCODEDESC* m_next;
};

struct CRect
{
    float yMin;
    float xMin;
    float yMax;
    float xMax;
};

struct GLYPHBITMAPDATA
{
    void* m_data;
    uint32_t m_dataSize;
    uint32_t m_glyphWidth;
    uint32_t m_glyphHeight;
    int m_glyphCellWidth;
    float m_glyphAdvance;
    float m_glyphBearing;
    uint32_t m_glyphPitch;
    int32_t m_yOffset;
    int32_t m_yStart;
    CRect m_textureCoords;
};


struct TSHashObject_CHARCODEDESC_HASHKEY_NONE
{
    uint32_t m_hashval;
    TSLink_CHARCODEDESC m_linktoslot;
    TSLink_CHARCODEDESC m_linktofull;
    void* m_key;
};

struct CHARCODEDESC
{
    TSHashObject_CHARCODEDESC_HASHKEY_NONE hashObject;
    TSLink_CHARCODEDESC textureRowLink;
    TSLink_CHARCODEDESC fontGlyphLink;
    uint32_t textureNumber;
    uint32_t rowNumber;
    uint32_t glyphStartPixel;
    uint32_t glyphEndPixel;
    GLYPHBITMAPDATA bitmapData;
};

struct TSList_CHARCODEDESC
{
    ptrdiff_t m_linkoffset;
    TSLink_CHARCODEDESC m_terminator;
};


struct TEXTURECACHEROW
{
    uint32_t widestFreeSlot;
    TSList_CHARCODEDESC glyphlist;
};

struct TSBaseArray_TEXTURECACHEROW
{
    unsigned int m_alloc;
    unsigned int m_count;
    TEXTURECACHEROW* m_data;
};

struct CGxFont;
struct TEXTURECACHE
{
    DWORD m_texture;
    CGxFont* m_theFace;
    int8_t m_anyDirtyGlyphs;
    int8_t pad[3];
    TSBaseArray_TEXTURECACHEROW m_textureRows;
};


struct CGxFont
{
    char pad[0x64];
    TSList_CHARCODEDESC m_activeCharacterCache;
    uint32_t m_fontFaceHandle;
    char m_fontName[260];
    uint32_t m_cellHeight;
    uint32_t m_baseline;
    uint32_t m_fontFlags;
    float m_fontHeight;
    float m_pixelsPerUnit;
    TEXTURECACHE m_textureCache[8];
    uint32_t m_pixelSize;
};

const uint32_t textureScale = 256;

CLIENT_DETOUR(GxuFontInitialize, 0x006BE230, __stdcall, void, (void))
{
    const char* textShader = "UI-Text\0";
    Util::OverwriteUInt32AtAddress(0x006BE264, reinterpret_cast<uint32_t>(textShader));
    GxuFontInitialize();
}

CLIENT_DETOUR(TEXTURECACHE__CreateTexture, 0x00991320, __cdecl, void, (TEXTURECACHE * self, int a2))
{
    Util::OverwriteUInt32AtAddress(0x006CA08E, textureScale);
    Util::OverwriteUInt32AtAddress(0x006CA093, textureScale);
    Util::SetByteAtAddress((void*)0x006CA08A, 0x2);
    Util::SetByteAtAddress((void*)0x006CA08C, 0x2);
    TEXTURECACHE__CreateTexture(self, a2);
}

static uint32_t s_textureData[textureScale * textureScale];

void WriteTGA32(const char* filename)
{
    FILE* f = fopen(filename, "wb");
    if (!f)
        return;

    const uint16_t width  = textureScale;
    const uint16_t height = textureScale;

    // 18-byte TGA header
    uint8_t header[18] = {};
    header[2]          = 2; // uncompressed true-color
    header[12]         = width & 0xFF;
    header[13]         = width >> 8;
    header[14]         = height & 0xFF;
    header[15]         = height >> 8;
    header[16]         = 32;   // 32 bits per pixel
    header[17]         = 0x08; // 8 bits alpha
    fwrite(header, 1, 18, f);

    // write pixels (B G R A)
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            uint32_t pix   = reinterpret_cast<uint32_t*>(s_textureData)[y * width + x];
            uint8_t a      = (pix >> 24) & 0xFF;
            uint8_t r      = (pix >> 16) & 0xFF;
            uint8_t g      = (pix >> 8) & 0xFF;
            uint8_t b      = pix & 0xFF;
            uint8_t buf[4] = {b, g, r, a};
            fwrite(buf, 1, 4, f);
        }
    }

    fclose(f);
    printf("TGA texture written successfully.\n");
}


CLIENT_FUNCTION(SMemAlloc, 0x0076E540, __stdcall, void*, (int size, char* a2, int a3, int a4));
CLIENT_FUNCTION(SMemFree, 0x0076E5A0, __stdcall, void, (void* block, char* a2, int a3, int a4));

inline void CalculateYOffset(unsigned int pixelHeight,
                             int baseline,
                             FT_Face face,
                             unsigned int glyphHeight,
                             int* yOffset,
                             int* yStart)
{
    int v6 = 0;
    int v8 = 0;

    if (glyphHeight <= pixelHeight)
    {
        int bitmap_top = face->glyph->bitmap_top;
        if (bitmap_top <= baseline)
        {
            v8 = baseline - bitmap_top;
        }
        else
        {
            v8 = 0;
            v6 = bitmap_top - baseline;
        }
    }
    else
    {
        v8 = 0;
    }

    int v10 = (v8 <= 0) ? 0 : v8;

    if (static_cast<int>(pixelHeight - glyphHeight) >= v10)
    {
        *yOffset = v6;
        *yStart  = v10;
    }
    else
    {
        *yOffset = pixelHeight - v10 - glyphHeight;
        *yStart  = pixelHeight - glyphHeight;
    }
}

CLIENT_DETOUR(IGxuFontGlyphRenderGlyph, 0x006C8CC0, __cdecl, char, (FT_Face face, uint32_t pixelSize, int charCode, int a4, GLYPHBITMAPDATA* bitmapData, int a6, int a7))
{
    auto ret = IGxuFontGlyphRenderGlyph(face, pixelSize, charCode, a4, bitmapData, a6, a7);
    if (ret)
    {
        auto charIndex = FT_Get_Char_Index(face, charCode);
        FT_Load_Glyph(face, charIndex, a6 != 0 ? 8386 : 8330);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_SDF);

        SMemFree(bitmapData->m_data, "free", 0, 0);
        size_t size = face->glyph->bitmap.pitch * face->glyph->bitmap.rows;
        void* data = SMemAlloc(size, __FILE__, __LINE__, 0);
        if (data)
        {
            memset(data, 0, size);
        }
        if (face->glyph->bitmap.buffer)
        {
            memcpy(data, face->glyph->bitmap.buffer, size);
        }
        bitmapData->m_glyphHeight = face->glyph->bitmap.rows;
        bitmapData->m_glyphWidth  = face->glyph->bitmap.width;
        bitmapData->m_glyphPitch  = face->glyph->bitmap.pitch;
        //bitmapData->m_glyphCellWidth = 64;
        bitmapData->m_dataSize = size;
        bitmapData->m_data     = data;

        int v8 = face->ascender + face->descender;
        float v9     = ((float)pixelSize * face->ascender) / (float)v8;
        int baseline = (int)(v9 + 0.5f);

        int yOffset = 0;
        //CalculateYOffset(pixelSize, baseline, face, bitmapData->m_glyphHeight, &yOffset, &bitmapData->m_yStart);

        bitmapData->m_yStart *= 4;
    }
    return ret;
}

CLIENT_DETOUR(TextureCallback, 0x006C9F50, __cdecl, void,
              (int a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, TEXTURECACHE* a6, uint32_t& a7,
               const void*& a8))
{
    if (a1 == 1)
    {
        //TextureCallback(a1, a2, a3, a4, a5, a6, a7, a8);
        //a6->m_theFace->m_cellHeight = 24;
        if (a6->m_textureRows.m_count && a6->m_theFace && a6->m_texture && a6->m_theFace->m_cellHeight)
        {
            int cellHeight = 32;

            memset(s_textureData, 0, textureScale * textureScale * 4);
            for (size_t i = 0; i < a6->m_textureRows.m_count; i++)
            {
                for (CHARCODEDESC* next = a6->m_textureRows.m_data[i].glyphlist.m_terminator.m_next;
                     next && (reinterpret_cast<uintptr_t>(next) & 1) == 0;
                     next = *reinterpret_cast<CHARCODEDESC**>((uintptr_t)next + a6->m_textureRows.m_data[i].glyphlist.m_linkoffset + 4))
                {

                    uint32_t offset = next->glyphStartPixel + ((next->rowNumber * cellHeight) * textureScale);
                    uint32_t* dst   = &s_textureData[offset];

                    auto src           = reinterpret_cast<uint8_t*>(next->bitmapData.m_data);
                    auto pitch         = next->bitmapData.m_glyphPitch;
                    auto dstCellStride = next->bitmapData.m_glyphWidth * 4;

                    printf("%d %d %d %d %d %d %d\n", a6->m_textureRows.m_count, next->glyphStartPixel, next->rowNumber,
                           a6->m_theFace->m_cellHeight, a6->m_textureRows.m_data[i].glyphlist.m_linkoffset, pitch,
                           dstCellStride);
                    for (int32_t y = 0; y < next->bitmapData.m_yStart; y++)
                    {
                        memset(dst, 0, dstCellStride);
                        dst += textureScale;
                    }

                    for (int32_t y = 0; y < next->bitmapData.m_glyphHeight; y++)
                    {
                        for (int32_t x = 0; x < next->bitmapData.m_glyphWidth; x++)
                        {
                            uint8_t sdf = src[x];
                            uint8_t a   = sdf;
                            uint8_t r   = 255;
                            uint8_t g   = 255;
                            uint8_t b   = 255;

                            dst[x] = (a << 24) | (r << 16) | (g << 8) | b;
                        }

                        src += pitch;
                        dst += textureScale;
                    }
                    auto glyphHeight = next->bitmapData.m_glyphHeight;
                    auto yStart      = next->bitmapData.m_yStart;
                    if (cellHeight - glyphHeight - yStart > 0 && cellHeight - glyphHeight != yStart)
                    {
                        for (int32_t y = 0; y < (int32_t)cellHeight - (int32_t)glyphHeight - yStart;
                             y++)
                        {
                            memset(dst, 0, dstCellStride);
                            dst += textureScale;
                        }
                    }
                }
            }

            WriteTGA32("testrender.tga");

            a7 = textureScale * 4;
            a8 = s_textureData;
        }
    }
    else
    {
        TextureCallback(a1, a2, a3, a4, a5, a6, a7, a8);
    }
}

//static uint32_t origGlyphCellWidth;

CLIENT_DETOUR_THISCALL(GenerateTextureCoords, 0x006C4380, void, (int rowNumber, int cellHeight))
{
    CHARCODEDESC* charcodedesc = reinterpret_cast<CHARCODEDESC*>(self);
    CRect rect{};

    float size = (float)(1.0f / textureScale);
    int n1     = rowNumber * 32;
    rect.yMax  = (cellHeight + n1) * size;
    rect.yMin  = n1 * size;
    rect.xMin  = charcodedesc->glyphStartPixel * size;
    rect.xMax  = size * (charcodedesc->glyphStartPixel + charcodedesc->bitmapData.m_glyphCellWidth);
    charcodedesc->bitmapData.m_textureCoords = rect;
}

//CLIENT_DETOUR_THISCALL(GLYPHBITMAPDATA__CopyFrom, 0x006C4190, void, (GLYPHBITMAPDATA *a2))
//{
//    a2->m_glyphCellWidth = origGlyphCellWidth;
//    GLYPHBITMAPDATA__CopyFrom(self, a2);
//}

//CLIENT_DETOUR_THISCALL(GetGlyphData, 0x006C2480, char, (int a2, int a3))
//{
//    CGxFont* font  = reinterpret_cast<CGxFont*>(self);
//    uint32_t prev  = font->m_pixelSize;
//    uint32_t prevC = font->m_cellHeight;
//    // font->m_pixelSize = 24;
//    // font->m_cellHeight = 24;
//    auto ret           = GetGlyphData(self, a2, a3);
//    font->m_pixelSize  = prev;
//    font->m_cellHeight = prevC;
//
//    return ret;
//}

CLIENT_DETOUR_THISCALL(TEXTURECACHE__Initialize, 0x006CA130, void, (void* a2, int a3))
{
    Util::OverwriteUInt32AtAddress(0x006CA13F, textureScale);
    Util::OverwriteUInt32AtAddress(0x006CA166, textureScale);
    TEXTURECACHE__Initialize(self, a2, a3);
}

CLIENT_DETOUR_THISCALL(TEXTURECACHEROW__CreateNewDesc, 0x006C5120, CHARCODEDESC*, (GLYPHBITMAPDATA * a2, int a3, int a4))
{
    Util::OverwriteUInt32AtAddress(0x006C529E, textureScale - 1);
    Util::OverwriteUInt32AtAddress(0x006C52F2, textureScale - 1);

    //origGlyphCellWidth   = a2->m_glyphCellWidth;
    //a2->m_glyphCellWidth = a2->m_glyphCellWidth * 4;
    auto ret = TEXTURECACHEROW__CreateNewDesc(self, a2, a3, a4);
    //a2->m_glyphCellWidth = origGlyphCellWidth;
    return ret;
}

CLIENT_DETOUR_THISCALL_NOARGS(TEXTURECACHE__UpdateDirty, 0x006C9D50, void)
{
    Util::OverwriteUInt32AtAddress(0x006C9D62, textureScale);
    Util::OverwriteUInt32AtAddress(0x006C9D67, textureScale);
    TEXTURECACHE__UpdateDirty(self);
}

CLIENT_DETOUR_THISCALL_NOARGS(CGxFont__UpdateDimensions, 0x006C22F0, bool)
{
    auto ret = CGxFont__UpdateDimensions(self);
    if (ret)
    {
        CGxFont* font = reinterpret_cast<CGxFont*>(self);
        //font->m_cellHeight = 32;
    }
    return ret;
}

CLIENT_DETOUR(FT_New_Library_Original, 0x00991320, __cdecl, int, (FT_Memory memory, FT_Library* alibrary))
{
    return FT_New_Library(memory, alibrary);
}

CLIENT_DETOUR(FT_Add_Default_Modules_Original, 0x00990650, __cdecl, void, (FT_Library library))
{
    FT_Add_Default_Modules(library);
}

CLIENT_DETOUR(FT_New_Memory_Face_Original, 0x00993370, __cdecl, int, (FT_Library library, FT_Byte* file_base, FT_Long file_size, FT_Long face_index, FT_Face *aface))
{
    return FT_New_Memory_Face(library, file_base, file_size, face_index, aface);
}

CLIENT_DETOUR(FT_Select_Charmap_Original, 0x009910F0, __cdecl, int, (FT_Face face, FT_Encoding encoding))
{
    return FT_Select_Charmap(face, encoding);
}

CLIENT_DETOUR(FT_Set_Pixel_Sizes_Original, 0x00992780, __cdecl, int, (FT_Face face, FT_UInt pixel_width, FT_UInt pixel_height))
{
    return FT_Set_Pixel_Sizes(face, pixel_width, pixel_height);
}

CLIENT_DETOUR(FT_Get_Char_Index_Original, 0x009911A0, __cdecl, int, (FT_Face face, FT_ULong charcode))
{
    return FT_Get_Char_Index(face, charcode);
}

CLIENT_DETOUR(FT_Load_Glyph_Original, 0x00992DA0, __cdecl, int, (FT_Face face, FT_UInt glyph_index, FT_Int32 load_flags))
{
    return FT_Load_Glyph(face, glyph_index, load_flags);
}

CLIENT_DETOUR(FT_Render_Glyph_Original, 0x00992B60, __cdecl, int, (FT_GlyphSlot slot, FT_Render_Mode render_mode))
{
    return FT_Render_Glyph(slot, FT_RENDER_MODE_SDF);
}

CLIENT_DETOUR(FT_Get_Kerning_Original, 0x00991050, __cdecl, int, (FT_Face face, FT_UInt left_glyph, FT_UInt right_glyph, FT_UInt kern_mode, FT_Vector* akerning))
{
    return FT_Get_Kerning(face, left_glyph, right_glyph, kern_mode, akerning);
}
