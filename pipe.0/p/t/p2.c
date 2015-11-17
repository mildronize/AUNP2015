#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	char	cmd[]="ls>file";
	int	ret;
	FILE	*fp;
	char	line[128];

	ret = system(cmd);
	printf("ret = %d\n", ret);
	fp = fopen("file", "r");
	while (!feof(fp)) {
		fscanf(fp, "%s", line);
		fprintf(stdout, "line = '%s'\n", line);
	}
	fclose(fp);
	
	return 0;
}
