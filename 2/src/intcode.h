#ifndef INTCODE_H
#define INTCODE_H

#include <stdlib.h>

struct intcode_program {
	size_t length;
	size_t ip;
	int* instructions;
};
typedef struct intcode_program intcode_program;

intcode_program* str_to_intcode_program(char raw[]);

void intcode_program_free(intcode_program *program);

int program_peek(intcode_program *program, size_t index);
void program_poke(intcode_program *program, size_t index, int value);

#endif // INTCODE_H
