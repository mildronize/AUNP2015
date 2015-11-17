#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	char	cmd[]="ls";
	int	ret;
	FILE	*fp;
	char	line[128];

	fp = popen(cmd, "r");
	while (!feof(fp)) {
		fscanf(fp, "%s", line);
		fprintf(stdout, "line = '%s'\n", line);
	}
	fclose(fp);
	
	return 0;
}
