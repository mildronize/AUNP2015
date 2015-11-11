#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CMD	"ls -la"
#define	BUFSZ	256

int	main(void) {
	FILE *f;

	f = popen(CMD, "r");
	if (f == (FILE *)NULL) {
		perror("popen"); exit(-1);
	}
	while(!feof(f)) {
		char	buf[BUFSZ];
		fgets(buf, sizeof(buf), f);
		printf("%s", buf);
	}
	pclose(f);

	return 0;
}
