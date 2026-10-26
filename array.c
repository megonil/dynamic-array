#include "array.h"

#include "utilities.h"

#include <stdlib.h>
#include <string.h>

void*
array_create (size_t initial_capacity, size_t item_size)
{
	size_t actual_capacity
		= max (ARRAY_INITIAL_CAPACITY, initial_capacity);
	ArrayHeader* header
		= calloc (1, sizeof (ArrayHeader) + item_size * actual_capacity);

	if (!header) {
		return 0;
	}

	header->capacity  = actual_capacity;
	header->size	  = 0;
	header->item_size = item_size;

	return header + 1;
}

void
array_free (void* array)
{
	free (array_header (array));
}

void*
array_ensure (void* array, size_t n)
{
	ArrayHeader* header			 = array_header (array);
	size_t		 needed_capacity = header->size + n;

	if (header->capacity < needed_capacity) {
		size_t new_capacity = header->capacity;
		while (new_capacity < needed_capacity) {
			new_capacity *= ARRAY_GROW_COEFF;
		}

		ArrayHeader* new_header = realloc (
			header,
			sizeof (ArrayHeader) + new_capacity * header->item_size);

		new_header->capacity = new_capacity;

		return new_header + 1;
	}

	// nothing
	return header + 1;
}

void*
array_clone (const void* array)
{
	void* new_array = array_create (cap (array), isize (array));
	if (!new_array)
		return 0;

	memmove (new_array, array, len (array) * isize (array));
	len (new_array) = len (array);

	return new_array;
}

uint
array_equals (void* a, void* b)
{
	return len (a) == len (b) && (memcmp (a, b, len (a) * isize (a)) == 0);
}

void
array_reverse (void* array)
{
	size_t		   isize = isize (array);
	unsigned char* temp	 = malloc (isize);

	for (size_t i = 0; i < len (array) / 2; ++i) {
		unsigned char* a = array + i * isize;
		unsigned char* b = array + (len (array) - i - 1) * isize;

		memcpy (temp, a, isize);
		memcpy (a, b, isize);
		memcpy (b, temp, isize);
	}
}

void*
array_reversed (const void* array)
{
	void* new_array = array_clone (array);
	reverse (new_array);

	return new_array;
}

void*
array_push_many (void* dest, const void* src)
{
	dest = array_ensure (dest, len (src));
	memmove (
		(char*) dest + len (dest) * isize (dest),
		src,
		len (src) * isize (src));

	len (dest) += len (src);

	return dest;
}

void
array_print (void* array, ArrayPrintFunction f, const char* sep)
{
	size_t		sz		 = isize (array);
	const char* separate = "";

	unsigned char* bytes = array;
	for (size_t i = 0; i < len (array); ++i) {
		printf ("%s", separate);
		unsigned char* element = bytes + i * sz;
		f (element, sz);
		separate = sep;
	}
}
