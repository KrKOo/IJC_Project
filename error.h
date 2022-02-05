// error.h
// Riešenie: IJC-DU1, príklad b), 23.3.2021
// Autor: Kristián Kováč, FIT
// Preložené: gcc 9.3.0
#ifndef __ERROR_H_
#define __ERROR_H_

extern void warning_msg(const char* fmt, ...);
extern void error_exit(const char* fmt, ...);

#endif //__ERROR_H_
