#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	char	cmd[]="wc -c";
	int	ret;
	FILE	*fp;
	char	line[128];

	fp = popen(cmd, "w");
	printf("input: ");
	fscanf(stdin, "%s", line);
	printf("line = '%s'\n", line);
	fprintf(fp, line);
	fclose(fp);
	
	return 0;
}
