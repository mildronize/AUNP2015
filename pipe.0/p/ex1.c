#include <stdio.h>
#include <stdlib.h>

int	main(void) {
	char *filename="/etc/passwd";
	FILE *fp;
	int	c, count;
	char	buf[4096];

	fp = fopen(filename, "r");
	if (fp == (FILE *)NULL) {
		perror("fopen"); exit(-1);
	}
	count=fread(buf, 1, sizeof(buf), fp);
	printf("read %d bytes\n", count);
	count=fwrite(buf, 1, count, stdout);
	fclose(fp);

	return 0;
}
