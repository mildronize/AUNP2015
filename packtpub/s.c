#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include <time.h>

#define	FILENAME	"a.txt"

int	main(void) {
	struct	stat	buf;
	struct	timeval	tv;

	gettimeofday(&tv, NULL);
	printf("current time of day = %s\n", ctime(&tv.tv_sec));

	stat(FILENAME, &buf);
	printf("ctime of file %s = %s\n", FILENAME, ctime(&buf.st_ctime));

	return 0;
}
