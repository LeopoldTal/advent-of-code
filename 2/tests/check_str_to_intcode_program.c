#include <stdlib.h>
#include <check.h>
#include "../src/intcode.h"

START_TEST(test_empty_program) {
	char raw[] = "";
	intcode_program *program;

	program = str_to_intcode_program(raw);
	ck_assert_int_eq(program->length, 0);
	ck_assert_int_eq(program->ip, 0);
	ck_assert_int_eq(program->state, PROGRAM_RUNNING);
	ck_assert_ptr_null(program->instructions);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_1_instruction_program) {
	char raw[] = "42";
	intcode_program *program;

	program = str_to_intcode_program(raw);
	ck_assert_int_eq(program->length, 1);
	ck_assert_int_eq(program->ip, 0);
	ck_assert_int_eq(program->state, PROGRAM_RUNNING);
	ck_assert_ptr_nonnull(program->instructions);
	ck_assert_int_eq(program->instructions[0], 42);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_2_instructions_program) {
	char raw[] = "3,14";
	intcode_program *program;

	program = str_to_intcode_program(raw);
	ck_assert_int_eq(program->length, 2);
	ck_assert_int_eq(program->ip, 0);
	ck_assert_int_eq(program->state, PROGRAM_RUNNING);
	ck_assert_ptr_nonnull(program->instructions);
	ck_assert_int_eq(program->instructions[0], 3);
	ck_assert_int_eq(program->instructions[1], 14);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_long_program) {
	char raw[] = "1,2,3,4,5,6,7,8,9,10,0,11,0,0,12,256,1024,0";
	int expected_instructions[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
		0, 11, 0, 0, 12, 256, 1024, 0
	};
	intcode_program *program;

	program = str_to_intcode_program(raw);
	ck_assert_int_eq(program->length, 18);
	ck_assert_int_eq(program->ip, 0);
	ck_assert_int_eq(program->state, PROGRAM_RUNNING);
	ck_assert_ptr_nonnull(program->instructions);
	ck_assert_mem_eq(program->instructions, expected_instructions, 18 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

Suite* str_to_intcode_program_suite() {
	Suite *s;
	TCase *tc_empty, *tc_simple, *tc_long;

	s = suite_create("Convert string to Intcode program");

	tc_empty = tcase_create("Empty program");
	tcase_add_test(tc_empty, test_empty_program);
	suite_add_tcase(s, tc_empty);

	tc_simple = tcase_create("Simple programs");
	tcase_add_test(tc_simple, test_1_instruction_program);
	tcase_add_test(tc_simple, test_2_instructions_program);
	suite_add_tcase(s, tc_simple);
	s = suite_create("Convert string to Intcode program");

	tc_long = tcase_create("Long program");
	tcase_add_test(tc_long, test_long_program);
	suite_add_tcase(s, tc_long);

	return s;
}
