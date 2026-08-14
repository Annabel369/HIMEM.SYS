#!/bin/bash
# conv2bmp.sh - Converte uma imagem para BMP compatível com DOS (640x480, 256 cores)
# Uso: ./conv2bmp.sh "foto.jpg" PIC5

DIR="/home/astral/Documentos/128GN CEAMARE"

# Verifica argumentos
if [ $# -lt 2 ]; then
    echo "Uso: $0 \"<imagem de entrada>\" <nome de saida sem extensao>"
    echo "Exemplo: $0 \"minha foto.jpg\" PIC5"
    exit 1
fi

INPUT="$1"
OUTPUT_NAME="$2"
OUTPUT="$DIR/${OUTPUT_NAME}.BMP"

# Verifica se o arquivo de entrada existe
if [ ! -f "$INPUT" ]; then
    # Tenta dentro do próprio diretório
    if [ -f "$DIR/$INPUT" ]; then
        INPUT="$DIR/$INPUT"
    else
        echo "Erro: arquivo '$INPUT' nao encontrado."
        exit 1
    fi
fi

# Verifica se a saída já existe
if [ -f "$OUTPUT" ]; then
    echo "Aviso: '$OUTPUT' ja existe. Nada foi feito."
    exit 0
fi

echo "Convertendo '$INPUT' -> '$OUTPUT' ..."

convert "$INPUT" \
    -resize 640x480! \
    -dither FloydSteinberg \
    -colors 256 \
    -type Palette \
    -compress None \
    BMP3:"$OUTPUT"

if [ $? -eq 0 ]; then
    echo "Pronto! Arquivo criado: $OUTPUT"
    identify "$OUTPUT"
else
    echo "Erro na conversao."
    exit 1
fi
