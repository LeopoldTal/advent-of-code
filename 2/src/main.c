#include <stdio.h>
#include <string.h>
#include "intcode.h"

int main(int argc, char **argv) {
	int target;
	char *buffer = NULL;
	size_t buffer_size = 0;

	if (argc < 2) {
		printf("Usage: intcode target-output\n");
		exit(EXIT_FAILURE);
	}
	target = atoi(argv[1]);

	getline(&buffer, &buffer_size, stdin);

	if (!buffer) {
		printf("Couldn't read input.\n");
		exit(EXIT_FAILURE);
	}

	printf("%d\n", program_find_inputs(buffer, target));
	free(buffer);

	return 0;
}
