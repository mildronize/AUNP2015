#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	printf("my pid = %d\n", getpid());
	printf("my parent pid = %d\n", getppid());
	return 0;
}
