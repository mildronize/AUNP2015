/*
 * reverse.c
 * reverse character in input word, used by popen3 program to
 * try popen for both read and write.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(void) {
	char	line[80];
	int	len,i;

	while (1) {
		if(fgets(line,sizeof(line),stdin)==NULL) {
			/* End of file, no more input or error */
			exit(0);
		}
		len=strlen(line);
		for (i=len;i>=0;--i) {
			fputc(line[i],stdout);
		}
/*		printf("\n");	*/
	}

	return 0;
}
