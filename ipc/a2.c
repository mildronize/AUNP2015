#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	BUFSZ	1024

int	main(int argc, char **argv) {
	FILE *f;
	int	count=0;

/*	system("find * > out.txt");	*/
	f = popen("find *", "r");
	if (f == (FILE *)NULL) { perror("popen"); exit(-1); }
	while (!feof(f)) {
		char	buf[BUFSZ];
		if (fgets(buf, sizeof(buf), f) != (char *)NULL) {
			count++;
			fprintf(stderr, "%d buf=%s", count, buf);
		}
	}
	pclose(f);
	fprintf(stderr, "%d files exist\n", count);

	return 0;
}

