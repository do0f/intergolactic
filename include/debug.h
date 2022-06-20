#ifndef COURSEWORK_DEBUG_H
#define COURSEWORK_DEBUG_H

#include <stdio.h>

#define DEBUG 1
#define DEBUG_PRINT(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#endif