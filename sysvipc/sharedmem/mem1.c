#include <stdio.h>
#include <string.h>
#include <unistd.h>

char	buf[1024];

int	main(int argc, char *argv[]) {
	fprintf(stderr,"Buf address = 0x%X\n", (unsigned int)buf);
	memset(buf,0,sizeof(buf));	/* Clear buffer */
	if (argc!=1) {			/* if called with argument */
		strcpy(buf,argv[1]);	/* Copy it to buffer */
	}
	while (1) {
		fprintf(stderr,"buf[]='%s'\r",buf);
		sleep(1);
	}
	return 0;
}
