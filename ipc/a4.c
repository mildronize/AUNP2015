#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	BUFSZ	1024

int	main(int argc, char **argv) {
	FILE *f;
	int	i;

	f = popen("wc -l", "w");
	if (f == (FILE *)NULL) { perror("popen"); exit(-1); }
	/* process */
	for (i=0;i<10;i++) {
		fprintf(f, "line %d\n",i);
	}
	/* process end */
	pclose(f);

/*	system("cat out.txt | wc -l");	*/

	return 0;
}

