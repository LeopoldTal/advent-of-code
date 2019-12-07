#ifndef INTCODE_H
#define INTCODE_H

#include <stdlib.h>

enum PROGRAM_STATE {
	PROGRAM_RUNNING,
	PROGRAM_HALTED,
	PROGRAM_ERROR
};

enum OPCODE {
	OPCODE_ADD = 1,
	OPCODE_MULT = 2,
	OPCODE_HALT = 99
};

struct intcode_program {
	size_t length;
	size_t ip;
	enum PROGRAM_STATE state;
	int* instructions;
};
typedef struct intcode_program intcode_program;

intcode_program* str_to_intcode_program(char raw[]);

void intcode_program_free(intcode_program *program);

int program_peek(intcode_program *program, size_t index);
void program_poke(intcode_program *program, size_t index, int value);

void program_step(intcode_program *program);
void program_run(intcode_program *program);

int program_run_with_input(char raw[], int noun, int verb);
int program_run_with_alarm(char raw[]);

#endif // INTCODE_H
