#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>

void set_vesa_mode(int mode) {
    union REGS regs;
    regs.x.ax = 0x4F02;
    regs.x.bx = mode;
    int86(0x10, &regs, &regs);
}

void set_vesa_bank(int bank) {
    union REGS regs;
    regs.x.ax = 0x4F05;
    regs.x.bx = 0;
    regs.x.dx = bank;
    int86(0x10, &regs, &regs);
}

void set_palette(unsigned char index, unsigned char r, unsigned char g, unsigned char b) {
    outp(0x03C8, index);
    outp(0x03C9, r);
    outp(0x03C9, g);
    outp(0x03C9, b);
}

int main() {
    FILE *fp;
    unsigned char palette[1024];
    unsigned char far *vga = (unsigned char far *)MK_FP(0xA000, 0);
    int i, x, y;
    unsigned char *buffer;
    long offset;
    int current_bank = -1;
    int new_bank;
    int w = 640, h = 480;
    unsigned int vga_offset;

    fp = fopen("PIC.BMP", "rb");
    if (!fp) {
        printf("Erro ao abrir PIC.BMP\n");
        return 1;
    }

    fseek(fp, 54, SEEK_SET);
    fread(palette, 1, 1024, fp);

    set_vesa_mode(0x101);

    for (i = 0; i < 256; i++) {
        set_palette(i, palette[i*4+2] >> 2, palette[i*4+1] >> 2, palette[i*4] >> 2);
    }

    buffer = (unsigned char *)malloc(640);
    for (y = h - 1; y >= 0; y--) {
        fread(buffer, 1, 640, fp);
        
        offset = (long)y * w;
        new_bank = offset >> 16;
        vga_offset = offset & 0xFFFF;
        
        if (new_bank != current_bank) {
            set_vesa_bank(new_bank);
            current_bank = new_bank;
        }

        for (x = 0; x < w; x++) {
            vga[vga_offset] = buffer[x];
            vga_offset++;
            if (vga_offset == 0) {
                current_bank++;
                set_vesa_bank(current_bank);
            }
        }
    }
    
    free(buffer);
    fclose(fp);

    getch();
    
    {
        union REGS regs;
        regs.x.ax = 0x0003;
        int86(0x10, &regs, &regs);
    }

    return 0;
}
