#include "RamMonitor.h"
#ifdef _WIN32
#include <windows.h>

int RamMonitor::getUsagePercent()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    return (int)statex.dwMemoryLoad;
}
#else
int RamMonitor::getUsagePercent() { return 0; }
#endif
