#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CMD	"wc -c -w"

int	main(int argc, char **argv) {
	FILE	*f;
	int	i;

	f=popen(CMD, "w");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	system("ps auxw");
	for (i=1;i<argc;i++) {
		fprintf(stderr, "argv[%d] = '%s'\n", i, argv[i]);
		fprintf(f, "%s\n", argv[i]);
	}
	pclose(f);
	
	return 0;
}
