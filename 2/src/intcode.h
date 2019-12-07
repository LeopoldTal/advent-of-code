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

#endif // INTCODE_H
