#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CMD	"find ../. -name \\*.c > file.out"

int	main(int argc, char **argv) {
	FILE *f;

	system(CMD);
	f=fopen("file.out", "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	while (!feof(f)) {
		/* process each line */
	}
	fclose(f);
	
	return 0;
}
