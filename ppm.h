// ppm.h
// Riešenie: IJC-DU1, príklad b), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0

#ifndef __PPM_H_
#define __PPH_H_
#define MAXBUFLEN (8000 * 8000 * 3)

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

extern struct ppm *ppm_read(const char *filename);
extern void ppm_free(struct ppm *p);

#endif //__PPM_H_
