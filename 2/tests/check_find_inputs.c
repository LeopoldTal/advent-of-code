#include <check.h>
#include "../src/intcode.h"

START_TEST(test_find_inputs) {
	int ret;

	ret = program_find_inputs("1,99,99,0,2,0,1,0,1,0,4,0,99", 1214);
	ck_assert_int_eq(ret, 1202);
}
END_TEST

Suite* program_find_inputs_suite() {
	Suite *s;
	TCase *tc_find_inputs;

	s = suite_create("Find input for specified output");

	tc_find_inputs = tcase_create("Find input");
	tcase_add_test(tc_find_inputs, test_find_inputs);
	suite_add_tcase(s, tc_find_inputs);

	return s;
}
