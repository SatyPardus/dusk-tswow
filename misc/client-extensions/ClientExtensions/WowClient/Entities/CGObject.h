#pragma once

struct ObjectFields
{
    uint64_t OBJECT_FIELD_GUID;
    uint32_t OBJECT_FIELD_TYPE;
    uint32_t OBJECT_FIELD_ENTRY;
    float OBJECT_FIELD_SCALE_X;
    uint32_t OBJECT_FIELD_PADDING;
};

class CGObject
{
  public:
    void* vtable;
    uint32_t padding;
    ObjectFields* ObjectData;
    uint32_t ukn1[49];
};
