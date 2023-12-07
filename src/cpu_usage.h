//
// Created by woku on 12/7/2023.
//

#ifndef FILEEXPLORERIMGUI_CPU_USAGE_H
#define FILEEXPLORERIMGUI_CPU_USAGE_H


#include <vector>
class CpuUsage
{
public:
    CpuUsage();

private:
    std::vector<float> cpuHistory;
    std::vector<float> memoryHistory;

public:
    void PlotGraphs(float cpuUsage, size_t memoryUsage);
    void UpdateHistory(float cpuUsage, size_t memoryUsage);
    void SampleSystemUsage();
    float GetCPUUsage();
    size_t GetMemoryUsage();

};


#endif //FILEEXPLORERIMGUI_CPU_USAGE_H
