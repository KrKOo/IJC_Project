# Makefile
# Riešenie: IJC-DU1, 23.3.2021
# Autor: Kristián Kováč, FIT
# Preložené: gcc 9.3.0
# Makefile na preklad a zostavenie spustiteľných súborov

CC=gcc
CFLAGS= -g -std=c11 -pedantic -Wall -Wextra 
BINS = primes primes-i steg-decode
LIBS = -lm

all: $(BINS)

run: primes primes-i
	./primes
	./primes-i

primes: primes.c eratosthenes.c eratosthenes.h error.c error.h bitset.h
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

primes-i: primes.c eratosthenes.c eratosthenes.h error.c error.h bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE $^ -o $@ $(LIBS) 

steg-decode: steg-decode.c ppm.c ppm.h eratosthenes.c eratosthenes.h error.c error.h
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

zip:
	zip xkovac61.zip *.c *.h Makefile

clean:
	rm -f *.o
	rm -f $(BINS)
