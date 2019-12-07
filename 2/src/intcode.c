#include <stdlib.h>
#include <string.h>
#include "intcode.h"

intcode_program *str_to_intcode_program(char raw[]) {
	int MAX_PROGRAM_SIZE = 8; // TODO: dynamic

	int length = 0;
	char* cur_instruction;
	char* rest = raw;
	int *instructions = NULL;
	intcode_program *program;

	if (strlen(raw) > 0) {
		instructions = malloc(MAX_PROGRAM_SIZE * sizeof(int));
		if (!instructions) {
			return NULL;
		}

		cur_instruction = strtok_r(raw, ",", &rest);
		while (cur_instruction) {
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
	program->instructions = instructions;

	return program;
}
