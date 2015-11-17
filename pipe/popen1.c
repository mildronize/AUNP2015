/*
 * popen1.c
 * Try using popen(), open pipe as output.
 */

#include <stdio.h>
#include <stdlib.h>

#define	MAXLINE	255

int	main(void) {
	FILE *fp;
	int	i;

	if ((fp=popen("/usr/bin/wc -l","w"))==NULL) { 

/*	if ((fp=fopen("/tmp/t.txt","w"))==NULL) { */
		perror("popen"); exit(-1);
	}
	for (i=0;i<10;i++) {
		fprintf(fp,"Hello World\n");
	}
	pclose(fp);

	return 0;
}
