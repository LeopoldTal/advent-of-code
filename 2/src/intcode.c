#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intcode.h"

intcode_program *str_to_intcode_program(char raw[]) {
	const int BUFFER_INC_SIZE = 8; // small 'cuz I enjoy watching buffers grow

	int length = 0;
	int buffer_size = 0;

	char* cur_instruction;
	char* rest = raw;
	int *instructions = NULL;

	intcode_program *program;

	if (strlen(raw) > 0) {
		cur_instruction = strtok_r(raw, ",", &rest);
		while (cur_instruction) {
			if (buffer_size <= length) {
				buffer_size += BUFFER_INC_SIZE;
				instructions = realloc(instructions, buffer_size * sizeof(int));
				if (!instructions) {
					return NULL;
				}
			}

			instructions[length] = atoi(cur_instruction);
			length++;
			cur_instruction = strtok_r(NULL, ",", &rest);
		}
	}

	program = malloc(sizeof(intcode_program));
	if (!program) {
		return NULL;
	}
	
	program->length = length;
	program->ip = 0;
	program->state = PROGRAM_RUNNING;
	program->instructions = instructions;

	return program;
}

void intcode_program_free(intcode_program *program) {
	free(program->instructions);
	free(program);
}

int program_peek(intcode_program *program, size_t index) {
	if (!program) {
		printf("Tried to peek at position %zu but program is NULL.\n", index);
		exit(EXIT_FAILURE);
	}
	if (index >= program->length) {
		printf(
			"Tried to peek at position %zu but program length is only %zu.\n",
			index, program->length
		);
		exit(EXIT_FAILURE);
	}

	return program->instructions[index];
}

int program_peek_indirect(intcode_program *program, size_t indirect_index) {
	int index;
	index = program_peek(program, indirect_index);

	if (index >= program->length) {
		printf(
			"Tried to peek at position %d referenced at %zu but program length is only %zu.\n",
			index, indirect_index, program->length
		);
		program->state = PROGRAM_ERROR;
		return -1;
	}

	return program_peek(program, index);
}

void program_poke(intcode_program *program, size_t index, int value) {
	if (!program) {
		printf("Tried to poke %d at position %zu but program is NULL.\n", value, index);
		exit(EXIT_FAILURE);
	}
	if (index >= program->length) {
		printf(
			"Tried to poke %d at position %zu but program length is only %zu.\n",
			value, index, program->length
		);
		exit(EXIT_FAILURE);
	}

	program->instructions[index] = value;
}

void program_step(intcode_program *program) {
	int opcode, a, b, dest;

	if (program->state == PROGRAM_HALTED) {
		printf("Tried through step through already halted program.\n");
		exit(EXIT_FAILURE);
	}
	if (program->state == PROGRAM_ERROR) {
		printf("Tried through step through program but already failed with error.\n");
		exit(EXIT_FAILURE);
	}

	opcode = program_peek(program, program->ip);

	if (opcode == OPCODE_HALT) {
		program->state = PROGRAM_HALTED;
		return;
	}

	if (opcode != OPCODE_ADD && opcode != OPCODE_MULT) {
		printf("Bad opcode: %d at position %zu.\n", opcode, program->ip);
		program->state = PROGRAM_ERROR;
		return;
	}

	if (program->ip + 4 >= program->length) {
		printf("Unexpected program end at position %zu.\n", program->ip);
		program->state = PROGRAM_ERROR;
		return;
	}

	a = program_peek_indirect(program, program->ip + 1);
	b = program_peek_indirect(program, program->ip + 2);
	if (program->state == PROGRAM_ERROR) { // lookup failed
		return;
	}

	dest = program_peek(program, program->ip + 3);
	program_poke(program, dest, opcode == OPCODE_ADD ? a + b : a * b);

	program->ip += 4;
}

void program_run(intcode_program *program) {
	while (program->state == PROGRAM_RUNNING) {
		program_step(program);
	}
}

int program_run_with_alarm(char raw[]) {
	intcode_program *program;
	int ret;

	program = str_to_intcode_program(raw);

	if (!program) {
		printf("Failed to build program!\n");
		exit(EXIT_FAILURE);
	}

	program_poke(program, 1, 12);
	program_poke(program, 2, 2);
	program_run(program);

	if (program->state == PROGRAM_ERROR) {
		printf("Error running program\n");
		intcode_program_free(program);
		exit(EXIT_FAILURE);
	}

	ret = program_peek(program, 0);
	intcode_program_free(program);
	return ret;
}
