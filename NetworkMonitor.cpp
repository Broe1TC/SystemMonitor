#include "NetworkMonitor.h"
#ifdef _WIN32
#include <windows.h>
#include <iphlpapi.h>

int NetworkMonitor::getSpeedKbPerSec()
{
    static DWORD prevBytes = 0;

    MIB_IFTABLE* pIfTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    dwRetVal = GetIfTable(nullptr, &dwSize, FALSE);
    if (dwRetVal == ERROR_INSUFFICIENT_BUFFER)
    {
        pIfTable = (MIB_IFTABLE*)malloc(dwSize);
        if (!pIfTable) return 0;
        dwRetVal = GetIfTable(pIfTable, &dwSize, FALSE);
        if (dwRetVal != NO_ERROR) { free(pIfTable); return 0; }

        DWORD totalBytes = 0;
        for (DWORD i = 0; i < pIfTable->dwNumEntries; i++)
        {
            MIB_IFROW row = pIfTable->table[i];
            totalBytes += row.dwInOctets + row.dwOutOctets;
        }
        free(pIfTable);

        int speed = (int)((totalBytes - prevBytes) / 1024); 
        prevBytes = totalBytes;
        return speed;
    }
    return 0;
}
#else
int NetworkMonitor::getSpeedKbPerSec() { return 0; }
#endif
