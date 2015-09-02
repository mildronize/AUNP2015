#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include <time.h>

#define	FILENAME	"a.txt"

int	main(int argc, char **argv) {
	struct	stat	buf;
	struct	timeval	tv;
	int	ret;

	gettimeofday(&tv, NULL);
	printf("current time of day = %s\n", ctime(&tv.tv_sec));

	ret=stat(argv[1], &buf);
	if (ret == 0) {
		printf("success\n");
	} else {
		perror("stat");
		exit(-1);
	}
	printf("ctime of file %s = %s\n", argv[1], ctime(&buf.st_ctime));

	return 0;
}
