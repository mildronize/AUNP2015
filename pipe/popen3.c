/*
 * popen3.c
 * Try using popen(), open pipe as both input, and output.
 *
 * NO! popen() can either "read" or "write" but can't do both at the same time.
 */

#include <stdio.h>
#include <stdlib.h>

#define	MAXLINE	255

int	main(void) {
	FILE	*fp;
	char	line[MAXLINE];

	printf("What are you looking for? pipe in popen is one way pipe.\n");
	exit(0);

	printf("Execute ./reverse program!\n");

	if ((fp=popen("./reverse","rw"))==NULL) {
		perror("popen('./reverse')"); exit(-1);
	}

	printf("Sending 'Hello World\\n' to pipe\n");
	fprintf(fp,"Hello World\n");

	fgets(line,sizeof(line),fp);
	printf("Receiving '%s'\n",line);

	pclose(fp);

	return 0;
}
