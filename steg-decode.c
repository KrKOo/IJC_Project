// steg-decode.c
// Riešenie: IJC-DU1, príklad b), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0
// Program na zistenie tajnej správy zakódovanej do obrázku výpočtom prvočíselných bytov pomocou Eratosthenovho sita a dynamického bitového poľa.
// Obmedzenie: Program podporuje len PPM typu P6 ktorých veľkosť nepresahuje 8000 * 8000 * 3 bytov.

#include <math.h>
#include <stdbool.h>

#include "bitset.h"
#include "eratosthenes.h"
#include "ppm.h"

int main(int argc, char* argv[]) {
    if (argc != 2) error_exit("Nebol zadany vstupny subor\n");

    struct ppm* image = ppm_read(argv[1]);
    if (image == NULL) error_exit("Subor %s sa nepodarilo nacitat\n", argv[1]);

    unsigned long imageSize = image->xsize * image->ysize * 3;
    bitset_alloc(bitset, imageSize * 8);

    Eratosthenes(bitset);

    unsigned char c = 0;
    int counter = 0;
    bool end = false;

    for (bitset_index_t i = 23; i < imageSize; i++) {
        if (!bitset_getbit(bitset, i)) {
            c >>= 1;
            c |= (image->data[i] & 1) * 128;

            if (++counter == 8) {
                if (c == 0) {
                    end = true;
                    break;
                }

                putchar(c);
                counter = 0;
                c = 0;
            }
        }
    }

    ppm_free(image);
    bitset_free(bitset);
    if (!end)
        error_exit("Sprava nebola ukoncena '\\0'\n");
    else
        putchar('\n');

    return 0;
}
