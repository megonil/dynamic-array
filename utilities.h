#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H

#include <stdio.h>

typedef unsigned uint;

#define max(a, b) (a > b ? a : b)

#define times_(x, T, var) for (T var = 0; var < x; ++var)
#define times(x) times_ (x, size_t, i)

#define eprint(fmt, ...) fprintf (stderr, fmt, ##__VA_ARGS__)
#define eprintln(fmt, ...) eprint (fmt "\n", ##__VA_ARGS__)

#endif // !MY_UTILITIES_H
