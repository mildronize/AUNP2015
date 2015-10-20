#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	char *args[20] = {"WHATEVER", "x", "x",  NULL};

	execv("/bin/ps", args);
	printf("After execute\n");
	exit(0);
}
