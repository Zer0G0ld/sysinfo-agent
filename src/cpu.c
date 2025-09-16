#include "../include/cpu.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <intrin.h>

// ---------------- WINDOWS ----------------
static void cpuid_get_vendor_name(char* vendor, char* name) {
    int cpuInfo[4] = {0};

    __cpuid(cpuInfo, 0);
    ((int*)vendor)[0] = cpuInfo[1]; // EBX
    ((int*)vendor)[1] = cpuInfo[3]; // EDX
    ((int*)vendor)[2] = cpuInfo[2]; // ECX
    vendor[12] = 0;

    __cpuid(cpuInfo, 0x80000002);
    memcpy(name, cpuInfo, 16);
    __cpuid(cpuInfo, 0x80000003);
    memcpy(name + 16, cpuInfo, 16);
    __cpuid(cpuInfo, 0x80000004);
    memcpy(name + 32, cpuInfo, 16);
    name[48] = 0;
}

static unsigned int cpuid_get_features() {
    int cpuInfo[4];
    unsigned int features = 0;

    __cpuid(cpuInfo, 1);
    if (cpuInfo[3] & (1 << 25)) features |= CPU_SSE;
    if (cpuInfo[3] & (1 << 26)) features |= CPU_SSE2;
    if (cpuInfo[2] & (1 << 0))  features |= CPU_SSE3;
    if (cpuInfo[2] & (1 << 28)) features |= CPU_AVX;

    __cpuidex(cpuInfo, 7, 0);
    if (cpuInfo[1] & (1 << 5)) features |= CPU_AVX2;

    return features;
}

// ---------------- Uso real da CPU ----------------
double get_cpu_usage_real(void) {
    static FILETIME prevIdle = {0}, prevKernel = {0}, prevUser = {0};
    FILETIME idle, kernel, user;

    if (!GetSystemTimes(&idle, &kernel, &user))
        return 0.0;

    if (prevIdle.dwLowDateTime == 0) {
        prevIdle = idle;
        prevKernel = kernel;
        prevUser = user;
        Sleep(500); // pausa breve para medir diferença
        if (!GetSystemTimes(&idle, &kernel, &user))
            return 0.0;
    }

    ULARGE_INTEGER id, kr, us, pid, pkr, pus;
    id.LowPart = idle.dwLowDateTime; id.HighPart = idle.dwHighDateTime;
    kr.LowPart = kernel.dwLowDateTime; kr.HighPart = kernel.dwHighDateTime;
    us.LowPart = user.dwLowDateTime; us.HighPart = user.dwHighDateTime;

    pid.LowPart = prevIdle.dwLowDateTime; pid.HighPart = prevIdle.dwHighDateTime;
    pkr.LowPart = prevKernel.dwLowDateTime; pkr.HighPart = prevKernel.dwHighDateTime;
    pus.LowPart = prevUser.dwLowDateTime; pus.HighPart = prevUser.dwHighDateTime;

    double idleDiff = (double)(id.QuadPart - pid.QuadPart);
    double totalDiff = (double)((kr.QuadPart - pkr.QuadPart) + (us.QuadPart - pus.QuadPart));

    prevIdle = idle;
    prevKernel = kernel;
    prevUser = user;

    return (totalDiff == 0.0) ? 0.0 : ((totalDiff - idleDiff) / totalDiff) * 100.0;
}

CPUInfo get_cpu_info(void) {
    CPUInfo info;
    memset(&info, 0, sizeof(CPUInfo));

    cpuid_get_vendor_name(info.manufacturer, info.name);
    info.features = cpuid_get_features();

    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    info.threads = sysInfo.dwNumberOfProcessors;

    DWORD len = 0;
    GetLogicalProcessorInformation(NULL, &len);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer =
        (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)malloc(len);
    if (buffer) {
        if (GetLogicalProcessorInformation(buffer, &len)) {
            DWORD count = len / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
            int cores = 0, l1 = 0, l2 = 0, l3 = 0;
            for (DWORD i = 0; i < count; i++) {
                if (buffer[i].Relationship == RelationProcessorCore) cores++;
                if (buffer[i].Relationship == RelationCache) {
                    CACHE_DESCRIPTOR c = buffer[i].Cache;
                    switch (c.Level) {
                        case 1: l1 += c.Size / 1024; break;
                        case 2: l2 += c.Size / 1024; break;
                        case 3: l3 += c.Size / 1024; break;
                    }
                }
            }
            info.cores = cores;
            info.l1_cache_kb = l1;
            info.l2_cache_kb = l2;
            info.l3_cache_kb = l3;
        }
        free(buffer);
    }

    HKEY hKey;
    DWORD mhz = 0, size = sizeof(DWORD);
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                    "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                    0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        RegQueryValueExA(hKey, "~MHz", NULL, NULL, (LPBYTE)&mhz, &size);
        RegCloseKey(hKey);
    }
    info.frequency_current = (double)mhz;
    info.frequency_max = (double)mhz;

    info.usage = get_cpu_usage_real();

    return info;
}
