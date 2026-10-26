#define _POSIX_C_SOURCE 200809L

#include "test.h"
#include "utilities.h"

#include <signal.h>
#include <string.h>

#define T(fn_name, desc)                                                  \
	temp_result = full_test_fn_name (fn_name) (desc);                     \
	if (temp_result) {                                                    \
		succeded++;                                                       \
		eprintln ("test `%s` succeded", desc);                            \
	} else                                                                \
		failed++;

static void
signal_handler (int signum)
{
	eprint ("caught a signal: ");
	switch (signum) {
	case SIGSEGV: eprintln ("sigsegv."); break;
	case SIGINT: eprintln ("sigint."); break;
	case SIGTERM: eprintln ("sigterm."); break;
	default: break;
	}
}

static void
test_setup ()
{
	struct sigaction sa;
	memset (&sa, 0, sizeof (sa));

	sa.sa_handler = signal_handler;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction (SIGINT, &sa, 0);
	sigaction (SIGTERM, &sa, 0);
	sigaction (SIGSEGV, &sa, 0);

	eprintln ("===== TEST START =====\n");
}

void
test_array ()
{
	uint failed = 0, succeded = 0, temp_result = 0;
	test_setup ();

	ARRAY_TESTS;

	uint total_tests		 = failed + succeded;
	uint succeded_percentage = succeded * 100 / total_tests;

	if (succeded == total_tests) {
		eprintln ("all test succeded.");
	} else {
		eprintln ("%u%% of tests succeded.", succeded_percentage);
	}

	eprintln ("\n=====  TEST END  =====");
}

#undef T
