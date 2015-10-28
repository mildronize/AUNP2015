#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define	BUFSZ	256

int	main(void) {
	char	tempname[BUFSZ];
	char	cmdbuf[BUFSZ];
	FILE	*f, *f2;
	char	needle[][BUFSZ] = {
			"ELF 64-bit LSB",
			"gzip compressed data",
			"empty"
		};

	sprintf(tempname, "/tmp/.setgitignore.%d", getpid());
	sprintf(cmdbuf, "file * > %s", tempname);
	system(cmdbuf);

	f = fopen(tempname, "r");
	f2 = fopen(".gitignore", "w");
	if (f == (FILE *)NULL) {
		perror("fopen"); exit(-1);
	}
	while(!feof(f)) {
		char	haystack[BUFSZ];
		int	i, found = 0;
		int	needlesize = sizeof(needle)/BUFSZ;

		fgets(haystack, sizeof(haystack), f);

		for (i=0;i<needlesize;i++) {
			if (strstr(haystack, needle[i])!=(char *)NULL) {
				found = 1;
				break;
			}
		}
		if (found) {
			char *ptr = index(haystack, ':');
			*ptr = '\0';
			fprintf(f2, "%s\n", haystack);
		}
	}
	fclose(f);
	fclose(f2);

	unlink(tempname);
	return 0;
}
