#ifndef ARRAY_TEST_H
#define ARRAY_TEST_H

#include "utilities.h"

#define ARRAY_TESTS                                                       \
	T (init, "array basic creating and free")                             \
	T (push1, "array push 1 element")                                     \
	T (push_many, "array push many elements")                             \
	T (len_cap_isize, "array's properly properties functions working")    \
	T (reverse, "proper reversing")                                       \
	T (reversed, "proper reversed array")                                 \
	T (clone, "array cloning")                                            \
	T (equals, "array equals")                                            \
	T (concat, "array concat")

#define full_test_fn_name(n) test_array_##n

#define T(fn_name, desc)                                                  \
	uint full_test_fn_name (fn_name) (const char* test_name);

ARRAY_TESTS

#undef T

/// the one function that launches all other ones
void
test_array ();

#endif // !ARRAY_TEST_H
