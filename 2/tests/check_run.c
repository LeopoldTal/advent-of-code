#include <check.h>
#include "../src/intcode.h"

START_TEST(test_program_1) {
	char raw[] = "1,9,10,3,2,3,11,0,99,30,40,50";
	int expected[] = {3500, 9, 10, 70, 2, 3, 11, 0, 99, 30, 40, 50};
	intcode_program *program;

	program = str_to_intcode_program(raw);

	program_run(program);

	ck_assert_int_eq(program->state, PROGRAM_HALTED);
	ck_assert_mem_eq(program->instructions, expected, 12 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_program_2) {
	char raw[] = "1,0,0,0,99";
	int expected[] = {2, 0, 0, 0, 99};
	intcode_program *program;

	program = str_to_intcode_program(raw);

	program_run(program);

	ck_assert_int_eq(program->state, PROGRAM_HALTED);
	ck_assert_mem_eq(program->instructions, expected, 5 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_program_3) {
	char raw[] = "2,3,0,3,99";
	int expected[] = {2, 3, 0, 6, 99};
	intcode_program *program;

	program = str_to_intcode_program(raw);

	program_run(program);

	ck_assert_int_eq(program->state, PROGRAM_HALTED);
	ck_assert_mem_eq(program->instructions, expected, 5 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_program_4) {
	char raw[] = "2,4,4,5,99,0";
	int expected[] = {2, 4, 4, 5, 99, 9801};
	intcode_program *program;

	program = str_to_intcode_program(raw);

	program_run(program);

	ck_assert_int_eq(program->state, PROGRAM_HALTED);
	ck_assert_mem_eq(program->instructions, expected, 6 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_program_5) {
	char raw[] = "1,1,1,4,99,5,6,0,99";
	int expected[] = {30, 1, 1, 4, 2, 5, 6, 0, 99};
	intcode_program *program;

	program = str_to_intcode_program(raw);

	program_run(program);

	ck_assert_int_eq(program->state, PROGRAM_HALTED);
	ck_assert_mem_eq(program->instructions, expected, 9 * sizeof(int));

	intcode_program_free(program);
}
END_TEST

START_TEST(test_bad_opcode) {
	intcode_program *program;

	program = str_to_intcode_program("1,99,1,4,99");

	program_run(program);

	ck_assert_int_eq(program->state, PROGRAM_ERROR);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_bad_length) {
	intcode_program *program;

	program = str_to_intcode_program("1,2,3,4,1,2,3,4");

	program_run(program);

	ck_assert_int_eq(program->state, PROGRAM_ERROR);

	intcode_program_free(program);
}
END_TEST

START_TEST(test_input) {
	int ret;

	ret = program_run_with_input("1,1000,1000,0,99", 4, 1);
	ck_assert_int_eq(ret, 103);
}
END_TEST

START_TEST(test_alarm) {
	int ret;

	ret = program_run_with_alarm("1,12,2,0,2,0,1,0,1,0,4,0,99");
	ck_assert_int_eq(ret, 1214);
}
END_TEST

Suite* program_run_suite() {
	Suite *s;
	TCase *tc_valid, *tc_invalid, *tc_input, *tc_alarm;

	s = suite_create("Run simple programs");

	tc_valid = tcase_create("Valid programs");
	tcase_add_test(tc_valid, test_program_1);
	tcase_add_test(tc_valid, test_program_2);
	tcase_add_test(tc_valid, test_program_3);
	tcase_add_test(tc_valid, test_program_4);
	tcase_add_test(tc_valid, test_program_5);
	suite_add_tcase(s, tc_valid);

	tc_invalid = tcase_create("Invalid programs");
	tcase_add_test(tc_valid, test_bad_opcode);
	tcase_add_test(tc_valid, test_bad_length);
	suite_add_tcase(s, tc_invalid);

	tc_input = tcase_create("With input");
	tcase_add_test(tc_input, test_input);
	suite_add_tcase(s, tc_input);

	tc_alarm = tcase_create("1202 alarm");
	tcase_add_test(tc_alarm, test_alarm);
	suite_add_tcase(s, tc_alarm);

	return s;
}
