#include <stdio.h>

int	main(void) {
	int	i;

	setvbuf(stdout,NULL,_IOFBF,0);	/* set stdout to full buffer */
	for (i=0;i<10;i++) {
		fprintf(stdout,"STDOUT:Hello World\n");
		sleep(1);
	}
	return 0;
}
