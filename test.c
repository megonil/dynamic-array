// tests return non zero value if test is successful, otherwise return 0
#include "test.h"

#include "array.h"

#include <assert.h>

#define t(f) uint full_test_fn_name (f) (const char* test_name)

#define prologue(T)                                                       \
	T*			array	= arrayc (T, ARRAY_INITIAL_CAPACITY);             \
	const char* context = 0

#define set_context(c) context = "(" c ") "

#define clear_context() context = 0

#define pro() prologue (int)
#define epi() array_free (array)

#define ok() return 1
#define err() return 0

#define initialize_0tox(arr, x)                                           \
	set_context ("while pushing");                                        \
	times (x)                                                             \
	{                                                                     \
		push (arr, i);                                                    \
	}

#define initialize_0to10(arr) initialize_0tox (arr, 10)

#define initialize_default_array() initialize_0to10 (array)

static void
print_arrays_int (unsigned char* bytes, size_t sz)
{
	assert (sz == sizeof (int));

	int* p = (int*) bytes;

	printf ("%d", *p);
}

static inline void
print_int (int v)
{
	printf ("%d", v);
}

static inline void
print_size_t (size_t v)
{
	printf ("%zu", v);
}

static inline void
print_int_array (int* v)
{
	printf ("[");
	array_print (v, print_arrays_int, ", ");
	printf ("]");
}

#define test_print_v(v)                                                   \
	_Generic (                                                            \
		(v),                                                              \
		int*: print_int_array,                                            \
		int: print_int,                                                   \
		size_t: print_size_t) (v)

#define assert_true(e)                                                    \
	if (!(e)) {                                                           \
		if (context != 0) {                                               \
			eprintln (                                                    \
				"test `%s`: %sassertion \"%s\" failed",                   \
				test_name,                                                \
				context,                                                  \
				#e);                                                      \
			err ();                                                       \
		} else {                                                          \
			eprintln (                                                    \
				"test `%s`: sassertion \"%s\" failed", test_name, #e);    \
			err ();                                                       \
		}                                                                 \
	}

#define assert_false(b) assert_true (!b)

#define assert_equal_impl(c, a, b)                                        \
	if (!(c)) {                                                           \
		if (context != 0) {                                               \
			eprintln (                                                    \
				"test `%s`: %sassertion \"%s\" failed",                   \
				test_name,                                                \
				context,                                                  \
				#c);                                                      \
			eprint ("\t\tleft = ");                                       \
			test_print_v (a);                                             \
			eprint (", right = ");                                        \
			test_print_v (b);                                             \
			eprintln ("\n");                                              \
			err ();                                                       \
		} else {                                                          \
			eprintln (                                                    \
				"test `%s`: sassertion \"%s\" failed", test_name, #c);    \
			err ();                                                       \
		}                                                                 \
	}

#define assert_equal(a, b) assert_equal_impl (a == b, a, b);

#define expect_at(i, v) assert_equal (array[i], v)

#define assert_arrays_equal(a, b)                                         \
	set_context ("checking that two arrays are equal");                   \
	assert_true (array_equals (a, b))

#define assert_arrays_not_equal(a, b)                                     \
	set_context ("checking that two arrays are not equal");               \
	assert_false (array_equals (a, b))

t (init)
{
	pro ();
	epi ();
	ok ();
}

t (push1)
{
	pro ();
	push (array, 1);

	set_context ("while pushing");
	expect_at (0, 1);

	epi ();
	ok ();
}

t (push_many)
{
	pro ();

	set_context ("while pushing");
	times (10)
	{
		push (array, i);
	}

	set_context ("while checking values");
	times (10)
	{
		expect_at (i, i);
	}

	epi ();
	ok ();
}

t (len_cap_isize)
{
	pro ();

	set_context ("while pushing");
	times (10)
	{
		push (array, i);
	}

	set_context ("while checking values");
	times (10)
	{
		expect_at (i, i);
	}

	set_context ("when checking len, cap and isize");
	assert_equal (len (array), 10);
	// we are asssuming that array's initial capacity is 8 and there
	// is only 1 grow happened
	assert_equal (cap (array), ARRAY_INITIAL_CAPACITY * ARRAY_GROW_COEFF);
	// because `pro` macro creates an array of ints
	assert_equal (isize (array), sizeof (int));

	epi ();
	ok ();
}
t (reverse)
{
	pro ();
	initialize_default_array ();

	reverse (array);
	set_context ("while checking");
	times (10)
	{
		assert_equal (10 - i - 1, array[i]);
	}

	epi ();
	ok ();
}

t (equals)
{
	pro ();

	initialize_default_array ();

	int* another_array = array (int);
	initialize_0to10 (another_array);

	assert_arrays_equal (array, another_array);
	push (another_array, 10);
	assert_arrays_not_equal (array, another_array);

	array_free (another_array);
	epi ();
	ok ();
}

t (clone)
{
	pro ();
	initialize_default_array ();

	int* cloned = clone (array);
	assert_arrays_equal (array, cloned);

	array_free (cloned);

	epi ();
	ok ();
}

t (reversed)
{
	pro ();
	initialize_default_array ();

	int* another_array = reversed (array);
	reverse (array);
	assert_arrays_equal (array, another_array);

	array_free (another_array);
	epi ();
	ok ();
}

t (concat)
{
	pro ();

	initialize_default_array ();

	int* another_array = array (int);
	initialize_0tox (another_array, 11);

	size_t previous_len = len (array);

	array_concat (array, another_array);

	set_context ("while checking");

	for (size_t i = previous_len; i < len (array); ++i) {
		assert_equal (array[i], another_array[i - previous_len]);
	}

	array_free (another_array);
	epi ();
	ok ();
}
