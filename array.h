#ifndef ARRAY_HEADER_H
#define ARRAY_HEADER_H

#include "utilities.h"

#include <stddef.h>

#define ARRAY_INITIAL_CAPACITY 8
#define ARRAY_GROW_COEFF 2

typedef struct {
	size_t size, capacity, item_size;
} ArrayHeader;

typedef void (*ArrayPrintFunction) (unsigned char*, size_t);

#define array(T) (T*) array_create (ARRAY_INITIAL_CAPACITY, sizeof (T))
#define arrayc(T, c) (T*) array_create (c, sizeof (T))

#define array_header(arr) ((ArrayHeader*) (arr) - 1)

#define len(arr) array_header (arr)->size
#define static_len(arr) sizeof (arr) / sizeof (arr[0])
#define cap(arr) array_header (arr)->capacity
#define isize(arr) array_header (arr)->item_size

#define push(arr, V)                                                      \
	do {                                                                  \
		arr				 = array_ensure (arr, 1);                         \
		arr[len (arr)++] = V;                                             \
	} while (0)

#define pop(arr) arr[len (arr)--]

#define foreach_(arr, T, var) for (T var = 0; var < len (arr); ++var)
#define foreach(arr, var) for (size_t var = 0; var < len (arr); ++var)

#define front(arr) arr[0]
#define back(arr) arr[len (arr) - 1]

#define array_concat(dest, src) dest = array_push_many (dest, src)

#define array_empty(arr) len (arr) == 0

#define reverse(arr) array_reverse (arr)
#define clone(arr) array_clone (arr)
#define reversed(arr) array_reversed (arr)

/// create array
void*
array_create (size_t initial_capacity, size_t item_size);

/// free array
void
array_free (void* array);

/// ensure array's fitting another n elements
void*
array_ensure (void* array, size_t n);

/// make a new array which is identical to the source one
void*
array_clone (const void* array);

/// reverse array
void
array_reverse (void* array);

/// return reversed clone of an array
void*
array_reversed (const void* array);

/// concatenate two arrays together
/// so that they become new array in form <dest><src>
void*
array_push_many (void* dest, const void* src);

/// check whether two arrays are equal
/// two arrays are equal if they have the same size and all corresponding
/// elements are equal
uint
array_equals (void* a, void* b);

/// print all array elements using f()
/// separating with sep
void
array_print (void* array, ArrayPrintFunction f, const char* sep);

#endif // !ARRAY_HEADER_H
