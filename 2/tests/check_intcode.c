#include <stdlib.h>
#include <check.h>
#include "../src/intcode.h"
#include "check_intcode.h"

int main() {
	int number_failed;
	SRunner *sr;

	sr = srunner_create(str_to_intcode_program_suite());
	srunner_add_suite(sr, program_peek_suite());
	srunner_add_suite(sr, program_poke_suite());

	srunner_run_all(sr, CK_VERBOSE);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return number_failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
