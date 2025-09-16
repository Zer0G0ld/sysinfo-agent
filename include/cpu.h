#pragma once
#include "agent.h"

// ---------------- Definições de instruções ----------------
#ifndef CPU_SSE
#define CPU_SSE    (1 << 0)
#endif
#ifndef CPU_SSE2
#define CPU_SSE2   (1 << 1)
#endif
#ifndef CPU_SSE3
#define CPU_SSE3   (1 << 2)
#endif
#ifndef CPU_AVX
#define CPU_AVX    (1 << 3)
#endif
#ifndef CPU_AVX2
#define CPU_AVX2   (1 << 4)
#endif

// ---------------- Estrutura de informações da CPU ----------------
typedef struct {
    char name[128];           // Nome/Modelo da CPU
    char manufacturer[64];    // Fabricante da CPU
    int cores;                // Número de núcleos físicos
    int threads;              // Número de threads lógicas
    int l1_cache_kb;          // Cache L1 em KB
    int l2_cache_kb;          // Cache L2 em KB
    int l3_cache_kb;          // Cache L3 em KB
    double frequency_current; // Frequência atual em MHz
    double frequency_max;     // Frequência máxima em MHz
    unsigned int features;    // Bitmask de instruções suportadas (SSE, AVX, AVX2, etc.)
    double usage;             // Uso atual da CPU em %
} CPUInfo;

// ---------------- Função principal ----------------
// Retorna informações completas da CPU
CPUInfo get_cpu_info(void);
