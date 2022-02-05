// ppm.c
// Riešenie: IJC-DU1, príklad b), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0
// Implementácia funkcií na čítanie obrázkov formátu PPM do dátovej štruktúry.
// Obmedzenie: Maximálna veľkosť obrázku je 8000 * 8000 * 3 bytov.

#include "ppm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bitset.h"
#include "error.h"

struct ppm *ppm_read(const char *filename) {
    struct ppm *res;
    if ((res = malloc(sizeof(struct ppm) + MAXBUFLEN)) == NULL) {
        warning_msg("ppm_read: Pri alokacii pamate pre %s nastal problem\n",
                    filename);
        return NULL;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        warning_msg("ppm_read: Subor %s sa nepodarilo otvorit\n", filename);
        ppm_free(res);
        return NULL;
    }

    char magicNumber[3] = {0};  // P6
    int maxColorValue;
    fscanf(file, "%2s %u %u %d ", magicNumber, &res->xsize, &res->ysize,
           &maxColorValue);

    if (strcmp(magicNumber, "P6") != 0) {
        warning_msg("ppm_read: Nevhodny format suboru %s\n", filename);
        ppm_free(res);
        fclose(file);
        return NULL;
    }

    fread(res->data, 1, MAXBUFLEN, file);
    if (ferror(file) != 0) {
        warning_msg("ppm_read: Nepodarilo sa precitat subor %s\n", filename);
        ppm_free(res);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return res;
}

void ppm_free(struct ppm *p) {
    free(p);
}
