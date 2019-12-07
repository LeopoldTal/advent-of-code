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
	program->instructions = instructions;

	return program;
}
