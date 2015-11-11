#include <stdio.h>
#include <unistd.h>

int	main(void) {
	int	i;

	for (i=0;i<10;i++) {
		fprintf(stdout,"STDOUT:Hello World");
		fprintf(stderr,"STDERR:Hello World");
		sleep(1);
	}
	return 0;
}
