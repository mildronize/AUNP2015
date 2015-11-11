#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void) {
	int	fd[2];
	int	pid;

	if (pipe(fd)==-1) {
		perror("pipe");
		exit(-1);
	}

	pid=fork();

	if (pid==-1) { perror("fork"); exit(-1); }
	if (pid==0) {	/* child */
		int	rfd = fd[0];
		char	buf[128];
		int	c;

		close(fd[1]);
	
		c = read(rfd, buf, sizeof(buf));
		printf("C: read %d bytes\n", c);
		buf[c] = 0;
		printf("C: buf = '%s'\n", buf);
		close(rfd);
		exit(0);
		
	} else {	/* parent */
		int	wfd = fd[1];
		char	buf[128];
		int	c;

		close(fd[0]);

		printf("input: ");
		scanf("%s", buf);
		c = write(wfd, buf, strlen(buf));
		printf("P: write '%s' count = %d\n", buf, c);
	}
	return 0;
}
