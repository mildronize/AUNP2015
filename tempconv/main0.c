#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * work with arguments
 */

int	main(int argc, char **argv) {
	int	i;

	printf("Number of argument = %d\n", argc);
	for (i=0;i<argc;i++) {
		printf("argument %d = '%s'\n", i, argv[i]);
	}

	return 0;
}
