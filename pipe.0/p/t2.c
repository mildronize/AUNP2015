#include <stdio.h>

int	main(void) {
	int	i;

	setbuf(stdout,NULL);	/* set no buffer for stdout */
	for (i=0;i<10;i++) {
		fprintf(stdout,"STDOUT:Hello World");
		sleep(1);
	}
	return 0;
}
