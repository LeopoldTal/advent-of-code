#include <check.h>
#include "../src/intcode.h"

START_TEST(test_halted) {
	intcode_program *program;

	program = str_to_intcode_program("1,2,3,4,0");
	program->state = PROGRAM_HALTED;

	program_step(program);
}
END_TEST

START_TEST(test_error) {
	intcode_program *program;

	program = str_to_intcode_program("1,2,3,4,0");
	program->state = PROGRAM_ERROR;

	program_step(program);
}
END_TEST

START_TEST(test_add_first_instruction) {
	char raw[] = "1,2,3,4,0";
	int expected_instructions[] = {1, 2, 3, 4, 7};
	intcode_program *program;

	program = str_to_intcode_program(raw);

	program_step(program);

	ck_assert_int_eq(program->length, 5);
	ck_assert_int_eq(program->ip, 4);
	ck_assert_int_eq(program->state, PROGRAM_RUNNING);
	ck_assert_mem_eq(program->instructions, expected_instructions, 5 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_add_mid_run) {
	char raw[] = "1,2,3,4,1,5,6,0,99";
	int expected_instructions[] = {11, 2, 3, 4, 1, 5, 6, 0, 99};
	intcode_program *program;

	program = str_to_intcode_program(raw);
	program->ip = 4;

	program_step(program);

	ck_assert_int_eq(program->length, 9);
	ck_assert_int_eq(program->ip, 8);
	ck_assert_int_eq(program->state, PROGRAM_RUNNING);
	ck_assert_mem_eq(program->instructions, expected_instructions, 9 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_mult) {
	char raw[] = "2,2,3,4,0";
	int expected_instructions[] = {2, 2, 3, 4, 12};
	intcode_program *program;

	program = str_to_intcode_program(raw);

	program_step(program);

	ck_assert_int_eq(program->length, 5);
	ck_assert_int_eq(program->ip, 4);
	ck_assert_int_eq(program->state, PROGRAM_RUNNING);
	ck_assert_mem_eq(program->instructions, expected_instructions, 5 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_halt) {
	intcode_program *program;

	program = str_to_intcode_program("99");

	program_step(program);

	ck_assert_int_eq(program->length, 1);
	ck_assert_int_eq(program->ip, 0);
	ck_assert_int_eq(program->state, PROGRAM_HALTED);
	ck_assert_int_eq(program->instructions[0], 99);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_bad_opcode) {
	intcode_program *program;

	program = str_to_intcode_program("42");

	program_step(program);

	ck_assert_int_eq(program->state, PROGRAM_ERROR);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_unexpected_program_end) {
	intcode_program *program;

	program = str_to_intcode_program("1,0,0");

	program_step(program);

	ck_assert_int_eq(program->state, PROGRAM_ERROR);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_index_out_of_range) {
	intcode_program *program;

	program = str_to_intcode_program("1,4,0,0");

	program_step(program);

	ck_assert_int_eq(program->state, PROGRAM_ERROR);

	intcode_program_free(program);
}
END_TEST

Suite* program_step_suite() {
	Suite *s;
	TCase *tc_bad_state, *tc_add, *tc_mult, *tc_halt, *tc_invalid;

	s = suite_create("Step through program");

	tc_bad_state = tcase_create("Bad program state");
	tcase_add_exit_test(tc_bad_state, test_halted, EXIT_FAILURE);
	tcase_add_exit_test(tc_bad_state, test_error, EXIT_FAILURE);
	suite_add_tcase(s, tc_bad_state);

	tc_add = tcase_create("Add");
	tcase_add_test(tc_add, test_add_first_instruction);
	tcase_add_test(tc_add, test_add_mid_run);
	suite_add_tcase(s, tc_add);

	tc_mult = tcase_create("Multiply");
	tcase_add_test(tc_mult, test_mult);
	suite_add_tcase(s, tc_mult);

	tc_halt = tcase_create("Halt");
	tcase_add_test(tc_halt, test_halt);
	suite_add_tcase(s, tc_halt);

	tc_invalid = tcase_create("Invalid program");
	tcase_add_test(tc_invalid, test_bad_opcode);
	tcase_add_test(tc_invalid, test_unexpected_program_end);
	tcase_add_test(tc_invalid, test_index_out_of_range);
	suite_add_tcase(s, tc_invalid);

	return s;
}
