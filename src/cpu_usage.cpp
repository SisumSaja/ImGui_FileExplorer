#include "cpu_usage.h"

float CpuUsage::GetCPUUsage()
{
    // Initialization (add this to your initialization code)
    PdhOpenQuery(nullptr, 0, &cpuQuery);
    PdhAddCounter(cpuQuery,reinterpret_cast<LPCSTR>(L"\\Processor(_Total)\\% Processor Time"), 0, &cpuTotal);
    PdhCollectQueryData(cpuQuery);

    PDH_FMT_COUNTERVALUE counterVal;
    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, nullptr, &counterVal);

    return static_cast<float>(counterVal.doubleValue);
}
CpuUsage::CpuUsage()
{

}
