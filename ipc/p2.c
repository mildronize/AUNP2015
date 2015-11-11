#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CMD	"wc -l"
#define	BUFSZ	256

int	main(char *argc, char **argv) {
	FILE *f;

	f=popen(CMD, "w");
	if (f == (FILE *)NULL) {
		perror("popen"); exit(-1);
	}
	

	return 0;
}
