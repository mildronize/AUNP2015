#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char	buf[256];

int	main(int argc, char *argv[]) {
	int	pid,c;
	char	buf2[256];

	fprintf(stderr,"Buf address = 0x%X\n", (unsigned int)buf);
	memset(buf,0,sizeof(buf));	/* Clear buffer */
	if (argc!=1) {			/* if called with argument */
		strcpy(buf,argv[1]);	/* Copy it to buffer */
	}

	fprintf(stderr,"Enter a word: ");
	scanf("%s",buf2);

	fprintf(stderr,"forking...\n");
	pid=fork();
	if (pid==-1) { perror("fork()"); exit(-1); }

	c='P'; 		/* assume parent */
	if (pid==0) {	/* copy buf2 to buf in child process */
		c='C';	/* child */
                fprintf(stderr,"Child copy buf2[]='%s', to buf[]='%s'\n",
				                                buf2, buf);

		strcpy(buf,buf2);
	}
	sleep(1);

	fprintf(stderr,"%c:buf[]='%s', buf2[]='%s'\n", c, buf, buf2);
	sleep(1);

	return 0;
}
