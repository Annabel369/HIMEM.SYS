<img width="1264" height="846" alt="Gemini_Generated_Image_de9owbde9owbde9o" src="https://github.com/user-attachments/assets/a946cfb9-6020-4701-87a6-2abac1d6f879" />
# HIMEM.SYS
HIMEM.SYS

# Entendendo o HIMEM.SYS

Este repositório contém informações históricas e técnicas sobre o arquivo **HIMEM.SYS**, um componente vital na era do MS-DOS.

> O HIMEM.SYS era um driver crítico para computadores com MS-DOS e versões antigas do Windows (3.x, 95 e 98). A sua função principal era atuar como um **gerenciador de memória estendida (XMS)**.

## O Contexto Histórico: O Problema da Memória no DOS

Para compreender a importância do HIMEM.SYS, precisamos analisar a arquitetura dos computadores antigos (baseados em processadores como o Intel 8086). Esses processadores tinham uma limitação severa: conseguiam endereçar diretamente apenas **1 Megabyte (MB)** de memória RAM.

Essa área de 1 MB era dividida da seguinte forma:

1.  **Memória Convencional (primeiros 640 KB):** Onde o DOS e a grande maioria dos programas (jogos, planilhas) precisavam rodar.
2.  **Memória Superior (restantes 384 KB):** Reservada para hardware, como BIOS e placas de vídeo.

Mesmo quando os computadores passaram a ter mais RAM (2 MB, 4 MB ou mais), sem um "truque" de software, o MS-DOS permanecia limitado aos 640 KB iniciais. Isso causava erros de "memória insuficiente" ao tentar rodar programas mais pesados, mesmo com RAM sobrando fisicamente.

## A Solução: HIMEM.SYS

O HIMEM.SYS resolvia este problema. Era um driver carregado no arranque do computador (via ficheiro `CONFIG.SYS`) que permitia ao sistema e aos programas ultrapassar a barreira de 1 MB.

### Principais Funções:

*   **Gerenciar a Memória Estendida (XMS):** Criava uma ponte padrão para que programas pudessem usar a RAM acima de 1 MB.
*   **Controlar a "High Memory Area" (HMA):** Gerenciava uma área especial de quase 64 KB logo acima da barreira de 1 MB, garantindo que apenas um programa a usasse de cada vez.
*   **Liberar Memória Convencional:** Permitia o uso do comando `DOS=HIGH` no `CONFIG.SYS`, movendo o núcleo do MS-DOS para a HMA. Isto libertava espaço nos preciosos 640 KB para que outros programas e jogos funcionassem.

## Resumo Visual da Gestão de Memória

| Tipo de Memória | Endereço | Sem HIMEM.SYS | Com HIMEM.SYS |
| :--- | :--- | :--- | :--- |
| **Estendida (XMS)** | Acima de 1 MB | Inacessível para a maioria dos programas. | Acessível para armazenar dados de programas compatíveis. |
| **High Memory Area (HMA)** | Logo acima de 1 MB | Não gerenciada. | Gerenciada. Pode conter o núcleo do DOS (`DOS=HIGH`). |
| **Barreira de 1 MB** | **1 MB** | **Fim da linha.** | **Ponte criada.** |
| **Convencional** | 0 a 640 KB | Cheia (DOS + drivers + programa). | Mais vazia (DOS movido para HMA, sobrando espaço para o programa). |
| **SHOWPIC2.EXE** | PIC4.BMP | 


## Como Contribuir

Se tiveres mais informações técnicas, diagramas ou curiosidades sobre a gestão de memória no DOS, sinta-se à vontade para abrir um Pull Request ou uma Issue.
