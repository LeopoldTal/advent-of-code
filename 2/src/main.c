#include <stdio.h>
#include "intcode.h"

int main() {
	char test_string[] = "3,14";

	intcode_program *program = NULL;
	int index;

	printf("%s\n", test_string);
	program = str_to_intcode_program(test_string);

	printf("Done converting:\n");
	printf("Length: %zu\n", program->length);
	for (index = 0 ; index < program->length ; index++) {
		printf("%d ", program->instructions[index]);
	}
	printf("\nIP: %zu\n", program->ip);

	return 0;
}
