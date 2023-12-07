//
// Created by woku on 12/7/2023.
//

#include "cpu_usage.h"
CpuUsage::CpuUsage()
{

}

float CpuUsage::GetCPUUsage()
{
    ULARGE_INTEGER li1, li2;
    FILETIME ft_SysIdle, ft_SysKernel, ft_SysUser;
    if(GetSystemTimes(&ft_SysIdle, &ft_SysKernel, &ft_SysUser))
    {
        li1.LowPart = ft_SysKernel.dwLowDateTime;
        li1.HighPart = ft_SysKernel.dwHighDateTime;

        li2.LowPart = ft_SysUser.dwLowDateTime;
        li2.HighPart = ft_SysUser.dwHighDateTime;

        auto kernelTime = li1.QuadPart;
        auto userTime = li2.QuadPart;

        // Calculate CPU usage percentage
        auto totalTime = kernelTime + userTime;
        auto idleTime = ft_SysIdle.dwHighDateTime | ft_SysIdle.dwLowDateTime;
        auto usageTime = totalTime - idleTime;

        return static_cast<float>(usageTime) / totalTime * 100.0f;
    }
    return 0.f;
}

size_t CpuUsage::GetMemoryUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return static_cast<size_t>(pmc.WorkingSetSize);
    }
    return 0;
}

void CpuUsage::PlotGraphs(float cpuUsage, size_t memoryUsage) {
    // Add the latest values to the history vectors
    cpuHistory.erase(cpuHistory.begin());
    cpuHistory.push_back(cpuUsage);

    memoryHistory.erase(memoryHistory.begin());
    memoryHistory.push_back(static_cast<float>(memoryUsage) / (1024 * 1024));

    // Plot the CPU Usage graph
    ImGui::Text("CPU Usage Graph:");
    ImGui::PlotLines("##cpuGraph", cpuHistory.data(), cpuHistory.size(), 0, nullptr, 0.0f, 100.0f, ImVec2(0, 80));

    // Plot the Memory Usage graph
    ImGui::Text("Memory Usage Graph:");
    ImGui::PlotLines("##memoryGraph", memoryHistory.data(), memoryHistory.size(), 0, nullptr, 0.0f, 1024.0f, ImVec2(0, 80));
}

void CpuUsage::UpdateHistory(float cpuUsage, size_t memoryUsage) {
    // Erase the oldest value
    cpuHistory.erase(cpuHistory.begin());
    memoryHistory.erase(memoryHistory.begin());

    // Add the latest values to the history vectors
    cpuHistory.push_back(cpuUsage);
    memoryHistory.push_back(static_cast<float>(memoryUsage) / (1024 * 1024));
}
void CpuUsage::SampleSystemUsage()
{
    // Display CPU Usage
    float cpuUsage = GetCPUUsage();
    ImGui::Text("CPU Usage: %.2f%%", cpuUsage);
    // Display Memory Usage
    size_t memoryUsage = GetMemoryUsage();
    ImGui::Text("Memory Usage: %zu MB", memoryUsage / (1024 * 1024));
    PlotGraphs(cpuUsage, memoryUsage);

}