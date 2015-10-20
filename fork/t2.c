#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv) {
	if (argc == 2) {
		int	i=atoi(argv[1]);
		printf("i = %d\n", i);
		exit(i);
	}
	exit(0);
}
