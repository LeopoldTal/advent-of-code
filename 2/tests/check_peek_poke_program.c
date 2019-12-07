#include <check.h>
#include "../src/intcode.h"

START_TEST(test_peek) {
	char raw[] = "613,18";
	intcode_program *program;

	program = str_to_intcode_program(raw);
	ck_assert_int_eq(program_peek(program, 0), 613);
	ck_assert_int_eq(program_peek(program, 1), 18);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_peek_null) {
	program_peek(NULL, 0);
}
END_TEST

START_TEST(test_peek_out_of_range) {
	char raw[] = "613,18";
	intcode_program *program;

	program = str_to_intcode_program(raw);
	program_peek(program, 2);
}
END_TEST

START_TEST(test_poke) {
	char raw[] = "1,2,3";
	intcode_program *program;

	program = str_to_intcode_program(raw);
	ck_assert_int_eq(program_peek(program, 1), 2);
	program_poke(program, 1, 1337);
	ck_assert_int_eq(program_peek(program, 1), 1337);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_poke_null) {
	program_poke(NULL, 0, 42);
}
END_TEST

START_TEST(test_poke_out_of_range) {
	char raw[] = "1,2,3";
	intcode_program *program;

	program = str_to_intcode_program(raw);
	program_poke(program, 3, 42);
}
END_TEST

Suite* program_peek_suite() {
	Suite *s;
	TCase *tc_peek, *tc_peek_null, *tc_peek_out_of_range;

	s = suite_create("Peek & poke program");

	tc_peek = tcase_create("Peek");
	tcase_add_test(tc_peek, test_peek);
	suite_add_tcase(s, tc_peek);

	tc_peek_null = tcase_create("Peek NULL");
	tcase_add_exit_test(tc_peek_null, test_peek_null, EXIT_FAILURE);
	suite_add_tcase(s, tc_peek_null);

	tc_peek_out_of_range = tcase_create("Peek out of range");
	tcase_add_exit_test(tc_peek_out_of_range, test_peek_out_of_range, EXIT_FAILURE);
	suite_add_tcase(s, tc_peek_out_of_range);

	return s;
}

Suite* program_poke_suite() {
	Suite *s;
	TCase *tc_poke, *tc_poke_null, *tc_poke_out_of_range;

	s = suite_create("Convert string to Intcode program");

	tc_poke = tcase_create("Poke");
	tcase_add_test(tc_poke, test_poke);
	suite_add_tcase(s, tc_poke);

	tc_poke_null = tcase_create("Poke NULL");
	tcase_add_exit_test(tc_poke_null, test_poke_null, EXIT_FAILURE);
	suite_add_tcase(s, tc_poke_null);

	tc_poke_out_of_range = tcase_create("Poke out of range");
	tcase_add_exit_test(tc_poke_out_of_range, test_poke_out_of_range, EXIT_FAILURE);
	suite_add_tcase(s, tc_poke_out_of_range);

	return s;
}
