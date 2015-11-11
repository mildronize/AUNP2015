#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	BUFSZ	1024

int	main(int argc, char **argv) {
	FILE *f;
	int	count=0;

	system("find * > out.txt");
	f = fopen("out.txt", "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	while (!feof(f)) {
		char	buf[BUFSZ];
		count++;
		fgets(buf, sizeof(buf), f);
	}
	fclose(f);
	fprintf(stderr, "%d files exist\n", count);

	return 0;
}

