# SysInfo Agent

**SysInfo Agent** é um agente de monitoramento de sistema desenvolvido em C, que coleta informações detalhadas do computador, como CPU, memória, disco, rede e sistema operacional. O projeto é modular e atualmente foca em **Windows**, mas pode ser estendido para Linux/macOS.

---

## Estrutura do Projeto

```text
sysinfo-agent/
├── bin/            # Executáveis compilados
├── build/          # Arquivos temporários de build
├── config/         # Arquivos de configuração
├── include/        # Cabeçalhos (.h) dos módulos
│   ├── agent.h
│   ├── cpu.h
│   ├── mem.h
│   ├── disk.h
│   ├── net.h
│   ├── os.h
│   └── json.h
├── src/            # Código fonte (.c)
├── testes/         # Scripts e arquivos de teste
├── Makefile        # Script de build
└── docs/           # Documentação dos módulos
```

---

## Módulos Disponíveis

### CPU

* Coleta informações detalhadas do processador:

  * Modelo e fabricante
  * Número de núcleos físicos e threads lógicas
  * Cache L1/L2/L3
  * Frequência atual e máxima
  * Instruções suportadas (SSE, AVX, AVX2)
  * Uso atual da CPU em percentual
* Implementação Windows usando:

  * `CPUID` e `__cpuid` / `__cpuidex`
  * `GetSystemInfo` e `GetLogicalProcessorInformation`
  * Registro do Windows para frequência (`~MHz`)
  * `GetSystemTimes` para uso real da CPU
* Estrutura principal: `CPUInfo`
* Documentação detalhada: `docs/cpu.md`

### Outros módulos (planejados)

* **Memória** — coleta uso de RAM, memória disponível e total.
* **Disco** — informações de partições, espaço usado e livre.
* **Rede** — interfaces, IPs e tráfego.
* **Sistema Operacional** — versão, arquitetura e hostname.
* **JSON** — serialização de dados para envio ou logging.

---

## Compilação

Exemplo de compilação no Windows:

```bash
cl /Fe:bin/test_cpu.exe src/cpu.c testes/test_cpu.c /link advapi32.lib kernel32.lib
```

Para build geral (com Makefile):

```bash
make
```

---

## Uso

```c
#include "cpu.h"

int main(void) {
    CPUInfo cpu = get_cpu_info();
    printf("CPU: %s, Uso: %.1f%%\n", cpu.name, cpu.usage);
    return 0;
}
```

---

## Contribuição

Contribuições são bem-vindas!
Planeje módulos adicionais, implemente funções de coleta e adicione testes correspondentes em `testes/`.

---

## Licença


