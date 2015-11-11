#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	FILE	*fp;

	fp=popen("./reverse","w");
	if (fp==NULL) {
		perror("popen"); exit(-1);
	}
	fprintf(fp,"Hello World\n");
	fprintf(fp,"How are you doing?\n");
	fprintf(fp,"I'm fine, thank you and you?\n");
	return 0;
}
