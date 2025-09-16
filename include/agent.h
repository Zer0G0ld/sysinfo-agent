typedef struct {
    char hostname[128];
    char os_version[128];

    // CPU
    char cpu_model[128];
    unsigned int cpu_cores;

    // Memória
    unsigned long long mem_total_mb;
    unsigned long long mem_free_mb;

    // Disco
    unsigned long long disk_total_gb;
    unsigned long long disk_free_gb;

    // Rede
    char ip_address[64];
} SysInfo;
