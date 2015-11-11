#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CMD	"find ../. -name \\*.c"

int	main(int argc, char **argv) {
	FILE *f;

//	system(CMD);
	f=popen(CMD, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	while (!feof(f)) {
		char buf[128];
		/* process each line */
		fgets(buf, sizeof(buf), f);
		printf("[%s]\n", buf);
	}
	pclose(f);
	
	return 0;
}
