#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <fcntl.h>

int	main(void) {
	char *filename="/etc/passwd";
	FILE *fp;

	int	fd;
	int	c, count;
	char	buf[4096];

	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("open"); exit(-1);
	}
	count=read(fd, buf, sizeof(buf));
	printf("read %d bytes\n", count);
	count=write(STDOUT_FILENO, buf, count);
	close(fd);

	return 0;
}
