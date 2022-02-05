// bitset.h
// Riešenie: IJC-DU1, príklad a), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0
// Implementáci makier a inline funkcií na prácu s bitovými poľami.

#ifndef __BITSET_H_
#define __BITSET_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

#define CHAR_BIT 8

typedef unsigned long bitset_t[];

typedef unsigned long bitset_index_t;

#define BITS_TO_UL_SIZE(bits)                                \
    ((bits % ((sizeof(unsigned long) * CHAR_BIT)))           \
         ? (bits / ((sizeof(unsigned long) * CHAR_BIT)) + 2) \
         : (bits / ((sizeof(unsigned long) * CHAR_BIT)) + 1))

#define BIT_INDEX_TO_UL(bit_index) \
    ((bit_index) / (sizeof(unsigned long) * CHAR_BIT) + 1)

#define bitset_create(name, size)                                     \
    unsigned long name[BITS_TO_UL_SIZE(size)] = {0};                  \
    static_assert(size > 0, "bitset_create: Zaporna velkost pola\n"); \
    name[0] = (size)

#define bitset_alloc(name, size)                                 \
    unsigned long *name =                                        \
        calloc(BITS_TO_UL_SIZE(size), sizeof(unsigned long));    \
    assert((size) > 0);                                          \
    if ((name) == NULL) {                                        \
        fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n"); \
    }                                                            \
    name[0] = (size)

#define bitset_free(name) free(name)

#ifndef USE_INLINE

#define bitset_size(name) name[0]

#define bitset_setbit(name, index, expression)                           \
    ((index >= bitset_size(name))                                        \
         ? ((error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", \
                        (unsigned long)index,                            \
                        (unsigned long)bitset_size(name) - 1)),          \
            0)                                                           \
         : ((expression != 0)                                            \
                ? (name[BIT_INDEX_TO_UL(index)] |=                       \
                   ((unsigned long)1                                     \
                    << (index % (sizeof(unsigned long) * 8))))           \
                : (name[BIT_INDEX_TO_UL(index)] &=                       \
                   ~((unsigned long)1                                    \
                     << (index % (sizeof(unsigned long) * 8))))))

#define bitset_getbit(name, index)                                            \
    ((index >= bitset_size(name))                                             \
         ? ((error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n",      \
                        (unsigned long)index,                                 \
                        (unsigned long)bitset_size(name) - 1)),               \
            0)                                                                \
         : (((name[BIT_INDEX_TO_UL(index)] &                                  \
              ((unsigned long)1 << (index % (sizeof(unsigned long) * 8)))) != \
             0)))

#else  // USE_INLINE

static inline unsigned long bitset_size(bitset_t name) {
    return name[0];
}

static inline void bitset_setbit(bitset_t name, bitset_index_t index,
                                 const int expression) {
    if (index >= bitset_size(name)) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n",
                   (unsigned long)index, (unsigned long)bitset_size(name) - 1);
    } else {
        (expression != 0)
            ? (name[BIT_INDEX_TO_UL(index)] |=
               ((unsigned long)1 << (index % (sizeof(unsigned long) * 8))))
            : (name[BIT_INDEX_TO_UL(index)] &=
               ~((unsigned long)1 << (index % (sizeof(unsigned long) * 8))));
    }
}

static inline int bitset_getbit(bitset_t name, bitset_index_t index) {
    if (index >= bitset_size(name)) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n",
                   (unsigned long)index, (unsigned long)bitset_size(name) - 1);
    } else {
        return (
            (index >= bitset_size(name))
                ? ((error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n",
                               (unsigned long)index,
                               (unsigned long)bitset_size(name) - 1)),
                   0)
                : (((name[BIT_INDEX_TO_UL(index)] &
                     ((unsigned long)1
                      << (index % (sizeof(unsigned long) * 8)))) != 0)));
    }
    return 0;
}

#endif  // USE_INLINE
#endif  // __BITSET_H_
