#pragma once

struct WoWClientDB
{
    void* funcTable;
    int isLoaded;
    int numRows;
    int maxIndex;
    int minIndex;
    int stringTable;
    void* funcTable2;
    int* FirstRow;
    int* Rows;
};
