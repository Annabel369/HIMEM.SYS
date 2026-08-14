#!/bin/bash
# Liga.sh - Abre o ambiente 128GN CEAMARE no DOSBox

# Cria symlink sem espacos (DOSBox nao suporta espacos no MOUNT)
ln -sfn "$(cd "$(dirname "$0")" && pwd)" /tmp/ceamare

CONF="/tmp/dosbox_ceamare_liga.conf"

cat > "$CONF" << 'ENDCONF'
[autoexec]
MOUNT C /tmp/ceamare
C:
MENU
ENDCONF

DISPLAY=:0 dosbox -conf "$CONF"
