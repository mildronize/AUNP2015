#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void) {
	int	fd[2];
	int	rfd, wfd;
	char	buf[256];
	char	xbuf[256];
	int	wsz,rsz;

	if (pipe(fd)==-1) {
		perror("pipe"); exit(-1);
	}

	rfd = fd[0];
	wfd = fd[1];
	sprintf(buf, "Hello World");

	printf("Reading...\n");
	rsz = read(wfd, xbuf, sizeof(xbuf));
	printf("Done reading %d...\n", rsz);

	printf("xbuf='%s'\n", xbuf);

	printf("Writing...\n");
	wsz = write(wfd, buf, strlen(buf));
	printf("Done writing %d...\n", wsz);

	return 0;
}
