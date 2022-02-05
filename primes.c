// primes.c
// Riešenie: IJC-DU1, príklad a), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0
// Výpočet posledných PRIME_COUNT prvočísel od 200 000 000 pomocou Eratosthenovho sita a bitového poľa.
// Meranie času výpočtu
// Obmedzenie: Pri vačších poliach je nutné zvýšiť veľkosť zásobníka.

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "bitset.h"
#include "eratosthenes.h"
#include "error.h"

#define PRIME_COUNT 10

int main() {
    clock_t start = clock();
    bitset_create(bitset, 200000000UL);
    Eratosthenes(bitset);

    int n = 0;
    bitset_index_t resArray[PRIME_COUNT] = {0};
    for (bitset_index_t i = bitset_size(bitset) - 1; n < PRIME_COUNT; i--) {
        if (!bitset_getbit(bitset, i)) {
            resArray[n++] = i;
        }
    }

    for (bitset_index_t i = 0; i < PRIME_COUNT; i++) {
        printf("%ld\n", resArray[PRIME_COUNT - 1 - i]);
    }

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}
