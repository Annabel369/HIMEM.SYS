/*
 * PLAYWAVE.C - Tocador WAV via Sound Blaster para MS-DOS / DOSBox
 * Compilar: BCC -ms -I\BCPP31\INCLUDE -L\BCPP31\LIB -ePLAYWAVE.EXE PLAYWAVE.C
 * Uso: PLAYWAVE MUSICAS\TOPGUN.WAV
 * Formato: WAV PCM 8-bit mono
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <conio.h>

/* ---- Portas Sound Blaster (A220) ---- */
#define SB_BASE     0x220
#define SB_RESET    (SB_BASE + 0x06)
#define SB_READ     (SB_BASE + 0x0A)
#define SB_RDSTAT   (SB_BASE + 0x0E)
#define SB_WRITE    (SB_BASE + 0x0C)
#define SB_ACK      (SB_BASE + 0x0E)

/* ---- Header WAV (sem padding) ---- */
#pragma pack(1)
typedef struct {
    char riff[4];
    long filesize;
    char wave[4];
    char fmtid[4];
    long fmtsize;
    int  format;
    int  channels;
    long samplerate;
    long byterate;
    int  blockalign;
    int  bitspersample;
    char dataid[4];
    long datasize;
} WAV_HDR;
#pragma pack()

/* ---- Funcoes DSP ---- */
static int sb_reset(void)
{
    int i;
    outp(SB_RESET, 1);
    delay(10);
    outp(SB_RESET, 0);
    delay(10);
    for (i = 0; i < 200; i++) {
        if (inp(SB_RDSTAT) & 0x80)
            if (inp(SB_READ) == 0xAA)
                return 1;
    }
    return 0;
}

static void sb_write(unsigned char val)
{
    while (inp(SB_WRITE) & 0x80)
        ;
    outp(SB_WRITE, val);
}

static void sb_set_rate(unsigned int rate)
{
    unsigned char tc = (unsigned char)(256 - (1000000UL / (unsigned long)rate));
    sb_write(0x40);
    sb_write(tc);
}

/* ---- Toca um bloco via DMA canal 1 e aguarda terminar ---- */
static void sb_play_block(unsigned char *buf, unsigned int len, unsigned int rate)
{
    unsigned long phys;
    unsigned int  lo, hi;
    unsigned char page;
    unsigned long ms;

    /* Endereco fisico do buffer near: DS:offset */
    phys = ((unsigned long)_DS << 4) + (unsigned long)(unsigned int)buf;
    lo   = (unsigned char)(phys & 0xFF);
    hi   = (unsigned char)((phys >> 8) & 0xFF);
    page = (unsigned char)((phys >> 16) & 0xFF);

    /* Programa DMA canal 1 */
    outp(0x0A, 0x05);        /* Mascara canal 1        */
    outp(0x0C, 0x00);        /* Limpa flip-flop        */
    outp(0x0B, 0x49);        /* Single, read, canal 1  */
    outp(0x02, lo);          /* Endereco low           */
    outp(0x02, hi);          /* Endereco high          */
    outp(0x83, page);        /* Pagina DMA             */
    outp(0x03, (len-1)&0xFF);/* Contador low           */
    outp(0x03, (len-1)>>8);  /* Contador high          */
    outp(0x0A, 0x01);        /* Desmascara canal 1     */

    /* Habilita speaker e inicia DMA single-cycle 8-bit */
    sb_write(0xD1);          /* Speaker ON             */
    sb_write(0x14);          /* DMA 8-bit single-cycle */
    sb_write((len-1) & 0xFF);
    sb_write((len-1) >> 8);

    /* Aguarda duracao do bloco (ms = len / rate * 1000) */
    ms = ((unsigned long)len * 1000UL) / (unsigned long)rate + 5UL;
    delay((unsigned int)ms);

    /* ACK da interrupcao DMA */
    inp(SB_ACK);
}

/* ================================================================ */
int main(int argc, char *argv[])
{
    FILE       *fp;
    WAV_HDR     hdr;
    unsigned char *buf;
    const char *fname;
    long        remaining;
    unsigned int chunk, blksize, rate;

    blksize = 512;
    fname   = (argc >= 2) ? argv[1] : "TOPGUN.WAV";

    printf("PLAYWAVE - Tocador WAV DOS\n");
    printf("==========================\n");

    fp = fopen(fname, "rb");
    if (!fp) {
        printf("Erro: nao abriu '%s'\n", fname);
        return 1;
    }

    fread(&hdr, sizeof(WAV_HDR), 1, fp);

    if (strncmp(hdr.riff, "RIFF", 4) != 0 || strncmp(hdr.wave, "WAVE", 4) != 0) {
        printf("Erro: arquivo WAV invalido.\n");
        fclose(fp); return 1;
    }
    if (hdr.format != 1 || hdr.bitspersample != 8) {
        printf("Erro: use WAV PCM 8-bit mono.\n");
        fclose(fp); return 1;
    }

    rate = (unsigned int)hdr.samplerate;

    printf("Arquivo : %s\n",     fname);
    printf("Taxa    : %u Hz\n",  rate);
    printf("Bits    : %d\n",     hdr.bitspersample);
    printf("Dados   : %ld bytes\n", hdr.datasize);
    printf("\nInicializando Sound Blaster...\n");

    if (!sb_reset()) {
        printf("Erro: SB nao encontrado em 0x%X!\n", SB_BASE);
        fclose(fp); return 1;
    }

    sb_set_rate(rate);

    buf = (unsigned char *)malloc(blksize);
    if (!buf) {
        printf("Erro: sem memoria.\n");
        fclose(fp); return 1;
    }

    printf("Tocando... (qualquer tecla para parar)\n\n");

    remaining = hdr.datasize;
    while (remaining > 0 && !kbhit()) {
        chunk = (remaining > (long)blksize) ? blksize : (unsigned int)remaining;

        if (fread(buf, 1, chunk, fp) < chunk)
            break;

        sb_play_block(buf, chunk, rate);
        remaining -= (long)chunk;
    }

    if (kbhit()) getch();

    sb_write(0xD3); /* Speaker OFF */
    sb_reset();
    free(buf);
    fclose(fp);

    printf("\nFim.\n");
    return 0;
}
