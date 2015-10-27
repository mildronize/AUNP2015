#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	int	i;

	for(i=0;i<5;i++) {
		fprintf(stdout, "%d ", i);
		sleep(1);
	}
	for(i=0;i<5;i++) {
		fprintf(stderr, "%d ", i);
		sleep(1);
	}
	fprintf(stdout, "\n");
	return 0;
}
