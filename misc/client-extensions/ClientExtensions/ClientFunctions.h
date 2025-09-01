#pragma once

#include "SharedDefines.h"
#include "ClientMacros.h"
#include "WowClient/C2Vector.h"
#include "WowClient/C3Vector.h"
#include "WowClient/Entities/CGPlayer.h"
#include "WowClient/DBC/SkillLineAbilityRow.h"
#include "WowClient/Events/TerrainClickEvent.h"

namespace CGChat {
    CLIENT_FUNCTION(AddChatMessage, 0x509DD0, __cdecl, bool, (char*, uint32_t, uint32_t, uint32_t, uint32_t*, uint32_t, char*, uint64_t, uint32_t, uint64_t, uint32_t, uint32_t, uint32_t*))
}

namespace CGGameUI {
    CLIENT_FUNCTION(DisplayError, 0x5216F0, __cdecl, void, (uint32_t, ...))
}

namespace CGPetInfo_C {
    CLIENT_FUNCTION(GetPet, 0x5D3390, __cdecl, uint64_t, (uint32_t))
}

namespace CGWorldFrame_C {
    CLIENT_FUNCTION(TranslateToMapCoords, 0x544140, __cdecl, bool, (C3Vector*, uint32_t, float*, float*, uint32_t, bool, uint32_t))
    CLIENT_FUNCTION(Intersect, 0x0077F310, __cdecl, char, (C3Vector*, C3Vector*, C3Vector*, float*, int, int))
}

namespace ClientDB {
    CLIENT_FUNCTION(GetRow, 0x65C290, __thiscall, void*, (void*, uint32_t))
    CLIENT_FUNCTION(GetLocalizedRow, 0x4CFD20, __thiscall, int, (void*, uint32_t, void*))
}

namespace ClientPacket {
    CLIENT_FUNCTION(MSG_SET_ACTION_BUTTON, 0x5AA390, __cdecl, void, (uint32_t, bool, bool))
}

namespace ClntObjMgr {
    CLIENT_FUNCTION(GetActivePlayer, 0x4D3790, __cdecl, uint64_t, ())
    CLIENT_FUNCTION(GetActivePlayerObj, 0x004038F0, __cdecl, CGPlayer*, ())
    CLIENT_FUNCTION(GetUnitFromName, 0x60C1F0, __cdecl, CGUnit*, (char*))
    CLIENT_FUNCTION(ObjectPtr, 0x4D4DB0, __cdecl, void*, (uint64_t, uint32_t))
}

namespace DNInfo {
    CLIENT_FUNCTION(AddZoneLight, 0x7ED150, __thiscall, void, (void*, int32_t, float))
    CLIENT_FUNCTION(GetDNInfoPtr, 0x7ECEF0, __stdcall, void*, ())
}

namespace FrameScript {
    CLIENT_FUNCTION(GetParam, 0x815500, __cdecl, bool, (lua_State*, int, int))
    CLIENT_FUNCTION(GetText, 0x819D40, __cdecl, char*, (char*, int, int))
    CLIENT_FUNCTION(SignalEvent, 0x81B530, __cdecl, int, (uint32_t, char*, ...))
}

namespace NTempest {
    CLIENT_FUNCTION(DistanceSquaredFromEdge, 0x7F9C90, __cdecl, bool, (int32_t, void*, C2Vector*, float*))
}

namespace SpellParser {
    CLIENT_FUNCTION(ParseText, 0x57ABC0, __cdecl, void, (void*, void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t))
}

namespace SErr {
    CLIENT_FUNCTION(PrepareAppFatal, 0x772A80, _cdecl, void, (uint32_t, const char*, ...))
}

namespace SFile {
    // Defs cherrypicked from StormLib: https://github.com/ladislav-zezula/StormLib
    CLIENT_FUNCTION(OpenFileEx, 0x424B50, __stdcall, bool, (HANDLE, const char*, uint32_t, HANDLE*))
    CLIENT_FUNCTION(ReadFile, 0x422530, __stdcall, bool, (HANDLE handle /*likely a handle*/, void* data, uint32_t bytesToRead, uint32_t* bytesRead, uint32_t* overlap /*just set to 0*/, uint32_t unk))
    CLIENT_FUNCTION(CloseFile, 0x422910, __stdcall, void, (HANDLE a1))

    //
    CLIENT_FUNCTION(OpenFile, 0x424F80, __stdcall, int, (char const* filename, HANDLE* a2 /*file handle out*/))
    CLIENT_FUNCTION(GetFileSize, 0x4218C0, __stdcall, DWORD /*lowest 32 bits in size*/, (HANDLE handle, DWORD* highSize /*highest 32 bits in size*/))
}

namespace SMem {
    CLIENT_FUNCTION(Alloc, 0x76E540, __stdcall, void*, (uint32_t, const char*, uint32_t, uint32_t))
    CLIENT_FUNCTION(Free, 0x76E5A0, __stdcall, bool, (void*, const char*, uint32_t, uint32_t))
}

namespace SStr {
    CLIENT_FUNCTION(Printf, 0x76F070, __cdecl, int, (char*, uint32_t, char*, ...))
    CLIENT_FUNCTION(Copy, 0x76ED20, __stdcall, char*, (char*, char*, uint32_t))
    CLIENT_FUNCTION(Copy_0, 0x76EF70, __stdcall, char*, (char*, char*, uint32_t))
    CLIENT_FUNCTION(Len, 0x76EE30, __stdcall, char*, (char*))
    CLIENT_FUNCTION(Chr, 0x76E6E0, __cdecl, char*, (char*, char))
}

namespace SysMsg {
    CLIENT_FUNCTION(Printf, 0x4B5040, __cdecl, int, (uint32_t, uint32_t, char*, ...))
}

CLIENT_FUNCTION(OsGetAsyncTimeMs, 0x86AE20, __cdecl, uint64_t, ())

CLIENT_FUNCTION(sub_61FEC0, 0x61FEC0, __thiscall, void, (void*, char*, char*, void*, void*, uint32_t))
CLIENT_FUNCTION(sub_6B1080, 0x6B1080, __cdecl, uint8_t, ())
CLIENT_FUNCTION(sub_6E22C0, 0x6E22C0, __thiscall, uint32_t, (void*, uint32_t))
CLIENT_FUNCTION(sub_812410, 0x812410, __cdecl, SkillLineAbilityRow*, (uint32_t, uint32_t, uint32_t))
CLIENT_FUNCTION(TerrainClick, 0x00527830, __cdecl, void, (TerrainClickEvent*))
CLIENT_FUNCTION(SStrCmpI, 0x0076E780, __stdcall, int, (char* text1, const char* text2, int length))
CLIENT_FUNCTION(TraceLine, 0x007A3B70, __cdecl, char, (C3Vector* start, C3Vector* end, C3Vector* hitPoint, float* distance, uint32_t flag, uint32_t optional))
