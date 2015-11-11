#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(void) {
	int	fd;

	printf("fd = %d\n", STDIN_FILENO);
	printf("fd = %d\n", STDOUT_FILENO);
	printf("fd = %d\n", STDERR_FILENO);

	return 0;
}

