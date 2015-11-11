/*
 * popen2.c
 * Try using popen(), open pipe as input.
 */

#include <stdio.h>
#include <stdlib.h>

#define	MAXLINE	255

int	main(void) {
	FILE	*fp;
	char	line[MAXLINE];

	if ((fp=popen("/bin/uname -a","r"))==NULL) {
		perror("popen"); exit(-1);
	}
	if (fgets(line, MAXLINE, fp)==NULL) {
		perror("fgets"); exit(-1);
	}
	printf("L=[%s]\n",line);
	pclose(fp);

	return 0;
}
