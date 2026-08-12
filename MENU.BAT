@ECHO OFF
CLS
ECHO.
ECHO  ======================================================
ECHO  *               MENU PRINCIPAL DO SISTEMA            *
ECHO  ======================================================
ECHO.
ECHO   [ 1 ] - Jogar Shadow Warrior
ECHO   [ 2 ] - Jogar Jumanji DOS
ECHO   [ 3 ] - Jogar Battle Chess 4000
ECHO   [ 4 ] - Desenhar no NeoPaint
ECHO   [ 5 ] - Desenhar no Deluxe Paint II (DP2)
ECHO   [ 6 ] - Programar: Turbo Pascal 7
ECHO   [ 7 ] - Programar: Borland C++ 3.1
ECHO   [ 8 ] - Iniciar TinyCore Linux (via GRUB4DOS)
ECHO   [ 9 ] - Iniciar TinyCore Linux (via LOADLIN)
ECHO   [ N ] - Abrir DOS Web Browser (Nosso Projeto)
ECHO   [ S ] - Sair para o DOS Puro
ECHO.
ECHO  ======================================================
CHOICE /C123456789NS /N "  -> Escolha a sua opcao [1-9, N, ou S]: "

IF ERRORLEVEL 11 GOTO SAIR
IF ERRORLEVEL 10 GOTO BROWSER
IF ERRORLEVEL 9 GOTO LINUX_LOADLIN
IF ERRORLEVEL 8 GOTO LINUX_GRUB
IF ERRORLEVEL 7 GOTO BCPP
IF ERRORLEVEL 6 GOTO PASCAL
IF ERRORLEVEL 5 GOTO DP2
IF ERRORLEVEL 4 GOTO NEOPAINT
IF ERRORLEVEL 3 GOTO CHESS
IF ERRORLEVEL 2 GOTO JUMANJI
IF ERRORLEVEL 1 GOTO GAME

:GAME
CLS
ECHO Carregando Shadow Warrior...
CD \GAME\SWARRIOR
SW.EXE
CLS
CD \
GOTO MENU

:JUMANJI
CLS
ECHO Carregando Jumanji DOS...
CD \GAME\JUMANJI
JUMANJI.EXE
CD \
MENU.BAT
GOTO MENU

:CHESS
CLS
ECHO Preparando ambiente para Battle Chess 4000...
CD \GAME\BCHESS4k
BC4000.EXE
CD \
MENU.BAT
GOTO MENU

:NEOPAINT
CLS
ECHO Iniciando NeoPaint...
CD \GAME\NEOPAINT
NEOPAINT.EXE
CD \
MENU.BAT
GOTO MENU

:DP2
CLS
ECHO Iniciando Deluxe Paint II...
CD \DP2
DP.EXE
CD \
MENU.BAT
GOTO MENU

:PASCAL
CLS
ECHO Iniciando Turbo Pascal 7...
CD \TP\BIN
TURBO.EXE
CD \
MENU.BAT
GOTO MENU

:BCPP
CLS
ECHO Iniciando Borland C++ 3.1...
CD \BCPP31\BIN
BC.EXE
CD \
MENU.BAT
GOTO MENU

:BROWSER
CLS
ECHO Iniciando o DOS Web Browser...
CD \BCPP31\BROWSER
BROWSER.EXE
CD \
MENU.BAT
GOTO MENU

:LINUX_GRUB
CLS
ECHO ======================================================
ECHO   Carregando TinyCore Linux (via GRUB.EXE)...
ECHO ======================================================
grub.exe --config-file="kernel /vmlinuz quiet loglevel=3 noembed; initrd /core.gz /addon.gz; boot"
ECHO.
ECHO Falha ao iniciar o GRUB. Voltando ao menu...
PAUSE
GOTO MENU

:LINUX_LOADLIN
CLS
ECHO ======================================================
ECHO   Carregando TinyCore Linux (via LOADLIN.EXE)...
ECHO ======================================================
loadlin vmlinuz initrd=initrd.gz quiet loglevel=3 noembed
ECHO.
ECHO Falha ao iniciar o Loadlin. Voltando ao menu...
PAUSE
GOTO MENU

:SAIR
CLS
ECHO.
ECHO ======================================================
ECHO   Sistema Liberado - MS-DOS Puro
ECHO.
ECHO   Dica: Para retornar a esta tela,
ECHO   digite MENU e pressione ENTER.
ECHO ======================================================
ECHO.
