
#pragma once
#include <vector>
#include <utility>
#include <QString>

class DiskMonitor {
public:
    std::vector<std::pair<QString, int>> getDiskInfo(); 
};
