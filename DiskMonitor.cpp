
#include "DiskMonitor.h"
#ifdef _WIN32
#include <windows.h>

std::vector<std::pair<QString, int>> DiskMonitor::getDiskInfo()
{
    std::vector<std::pair<QString, int>> disks;
    DWORD drives = GetLogicalDrives();
    for (int i = 0; i < 26; i++)
    {
        if (drives & (1 << i))
        {
            QString name = QString("%1:\\").arg(QChar('A' + i));
            ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes, totalNumberOfFreeBytes;
            if (GetDiskFreeSpaceExW((LPCWSTR)name.utf16(), &freeBytesAvailable, &totalNumberOfBytes, &totalNumberOfFreeBytes))
            {
                int used = 100 - int((totalNumberOfFreeBytes.QuadPart * 100) / totalNumberOfBytes.QuadPart);
                disks.push_back({ name, used });
            }
        }
    }
    return disks;
}
#else
std::vector<std::pair<QString, int>> DiskMonitor::getDiskInfo() { return {}; }
#endif
