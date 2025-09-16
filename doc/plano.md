Plano

Coleta de informações

CPU → GetSystemInfo

Memória → GlobalMemoryStatusEx

Disco → GetDiskFreeSpaceEx

OS → GetVersionEx (deprecated, mas ainda funciona em código simples) ou RtlGetVersion se quiser versão real.

Formato de saída

JSON simples no stdout

Depois você manda isso para o Zabbix via zabbix_sender ou implementa o protocolo.

Próximo passo

Expandir com WMI (ex.: número de série, modelo da placa, GPU, etc.).

Fluxo do Programa

Inicialização

Lê agent.conf (Zabbix server, hostname, intervalo, chave do item).

Prepara logging básico.

Coleta

cpu.c → núcleos, modelo (via WMI), clock.

mem.c → memória total, disponível.

disk.c → espaço total/livre (C:, D:\…).

os.c → versão do Windows, build.

net.c → hostname, IPs, MACs.

(depois dá pra expandir: GPU, BIOS, fabricante, serial).

Serialização

Tudo vai pra uma struct SysInfo.

Serializa em JSON (usando cJSON ou manualmente).

Envio

Opção A: grava em arquivo temporário + chama zabbix_sender.

Opção B: implementa protocolo nativo do Zabbix (TCP 10051).

Loop

Executa a cada interval segundos (config).

Loga sucesso/erro.