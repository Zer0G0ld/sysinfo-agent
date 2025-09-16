#include "../include/cpu.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h> // necessário para Sleep() e SetConsoleOutputCP()
#include <conio.h>   // necessário para _getch()
#endif

// Função para imprimir instruções suportadas
void print_features(unsigned int features) {
    if (features & CPU_SSE)   printf(" - SSE\n");
    if (features & CPU_SSE2)  printf(" - SSE2\n");
    if (features & CPU_SSE3)  printf(" - SSE3\n");
    if (features & CPU_AVX)   printf(" - AVX\n");
    if (features & CPU_AVX2)  printf(" - AVX2\n");
}

// Função para imprimir informações da CPU
void print_cpu_info(const CPUInfo* cpu) {
    printf("=== CPU Info ===\n");
    printf("Modelo: %s\n", cpu->name[0] ? cpu->name : "Desconhecido");
    printf("Fabricante: %s\n", cpu->manufacturer[0] ? cpu->manufacturer : "Desconhecido");
    printf("Cores físicos: %d\n", cpu->cores);
    printf("Threads lógicas: %d\n", cpu->threads);
    printf("Cache L1: %d KB\n", cpu->l1_cache_kb);
    printf("Cache L2: %d KB\n", cpu->l2_cache_kb);
    printf("Cache L3: %d KB\n", cpu->l3_cache_kb);
    printf("Frequência atual: %.0f MHz\n", cpu->frequency_current);
    printf("Frequência máxima: %.0f MHz\n", cpu->frequency_max);
    printf("Uso da CPU: %.1f%%\n", cpu->usage);

    printf("\nInstruções suportadas:\n");
    print_features(cpu->features);
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // habilita acentuação
#endif

    CPUInfo cpu = get_cpu_info();

#ifdef _WIN32
    Sleep(500); // espera breve para medir uso real
#endif

    cpu.usage = get_cpu_usage_real(); // atualiza uso real da CPU
    print_cpu_info(&cpu);

#ifdef _WIN32
    _getch(); // pausa antes de sair
#endif

    return 0;
}
