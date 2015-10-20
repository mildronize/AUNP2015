#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	printf("before fork()..\n");
	fork();
	printf("after fork()..\n");
	return 0;
}
