#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv) {
	FILE *f;
	char	buf[2048];
	int	count=0;

	f = fopen(argv[1], "r");
	if (f == (FILE *)NULL) {
		perror("fopen");
		exit(-1);
	}
	while(1) {
		char *s = fgets(buf, sizeof(buf), f);
		if (s == (char *)NULL)
			break;
		printf("%d: %s", ++count, buf);
	}

	fclose(f);

	return 0;
}
