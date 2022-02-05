// error.c
// Riešenie: IJC-DU1, príklad b), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0
// Implementáci pomocných funkcií na hlásenie chybových stavov programu.

#include "error.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define MESSAGE_PREFIX "CHYBA: "

void warning_msg(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, MESSAGE_PREFIX);
    vfprintf(stderr, fmt, args);
}

void error_exit(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, MESSAGE_PREFIX);
    vfprintf(stderr, fmt, args);

    exit(1);
}
