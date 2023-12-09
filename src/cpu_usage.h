#include "include.h"

class CpuUsage
{
public:
    CpuUsage();

    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;

    float GetCPUUsage();

};



