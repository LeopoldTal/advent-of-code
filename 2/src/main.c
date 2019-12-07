#include <stdio.h>
#include <string.h>
#include "intcode.h"

int main() {
	char *buffer = NULL;
	size_t buffer_size = 0;

	getline(&buffer, &buffer_size, stdin);

	if (!buffer) {
		printf("Couldn't read input.\n");
		exit(EXIT_FAILURE);
	}

	printf("%d\n", program_run_with_alarm(buffer));
	free(buffer);

	return 0;
}
