// eratosthenes.c
// Riešenie: IJC-DU1, príklad a), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0
// Implementácia algoritmu známim pod menom Eratosteneso sito. Algoritmus pracuje na bitovom poli.
#include <math.h>
#include <stdio.h>

#include "bitset.h"
#include "error.h"

void Eratosthenes(bitset_t array) {
    bitset_setbit(array, 0, 1);
    bitset_setbit(array, 1, 1);

    for (bitset_index_t i = 2; i < sqrt((double)bitset_size(array)); i++) {
        if (!bitset_getbit(array, i)) {
            for (bitset_index_t j = i * i; j < bitset_size(array); j += i) {
                bitset_setbit(array, j, 1);
            }
        }
    }
}
