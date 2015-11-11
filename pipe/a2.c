#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(int argc, char **argv) {
	int	fd;
	FILE	*f;
//	ssize_t	sz;

	char	buf[25];

	fd = open("t.txt", O_RDONLY);
	f = fdopen(fd, "r");
/*

	if (fd == -1) {
		perror("open"); exit(-1);
	}
	sz = read(fd, buf, sizeof(buf));
	if (sz == -1) {
		perror("read"); exit(-1);
	}
	printf("sz=%d\n, buf=[%s]\n", (int)sz, buf);
*/

	while(!feof(f)) {
		fgets(buf, sizeof(buf), f);
		printf("[%s]\n", buf);
	}
	close(fd);

	return 0;
}
