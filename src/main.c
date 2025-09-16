#include "../include/main.h"
#include "../include/cpu.h"
//#include "../include/mem.h"
//#include "../include/disk.h"
//#include "../include/os.h"
//#include "../include/net.h"
//#include "../include/json.h"

#include <stdio.h>

int init_agent(void) {
    // Inicializa WMI se necessário (CPU, BIOS, GPU)
    // init_wmi();
    return 1;
}

void run_agent(void) {
    // Criar a struct do sysinfo
    SysInfo info;

    // Coleta os dados
    CPUInfo cpu = get_cpu_info();
    info.cpu_cores = cpu.cores;
    snprintf(info.cpu_model, sizeof(info.cpu_model), "%s", cpu.name);

//    MemInfo mem = get_mem_info();
//    info.mem_total_mb = mem.total_mb;
//    info.mem_free_mb  = mem.free_mb;

//    DiskInfo disk = get_disk_info();
//    info.disk_total_gb = disk.total_gb;
//    info.disk_free_gb  = disk.free_gb;

//    OSInfo os = get_os_info();
//    snprintf(info.os_version, sizeof(info.os_version), "%s", os.name);

//    NetInfo net = get_net_info();
//    snprintf(info.ip_address, sizeof(info.ip_address), "%s", net.ip);

    // Serializa para JSON
    char *json = sysinfo_to_json(&info);
    printf("%s\n", json);

    // Aqui você pode chamar zabbix_sender ou implementar TCP direto
    free(json);
}

int main(void) {
    if (!init_agent()) {
        fprintf(stderr, "Erro ao inicializar agente\n");
        return 1;
    }

    run_agent();

    // cleanup_wmi(); // se você inicializou WMI

    return 0;
}
