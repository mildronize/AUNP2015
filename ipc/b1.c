#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define	FILENAME	"test.txt"

int	main(int argc, char **argv) {
	char	str[]="Hello World\n";
	char	*ptr;
	int	fd;
	int	size_to_write;
	int	size_written=0;
	int	count;

	fd = open(FILENAME, O_CREAT | O_WRONLY, 0600);
	size_to_write = strlen(str);
	ptr = str;
	while( size_written != strlen(str)) {
		fprintf(stderr, "before ptr = %08x\n", ptr);
		count = write(fd, ptr, size_to_write );
		fprintf(stderr, "after ptr = %08x\n", ptr);
		if (count == -1)  { perror("write"); exit(-1); }
		ptr += count;
		size_written += count;
		size_to_write -= count;
	}
	fprintf(stderr, "write %d bytes\n", count);
	close(fd);
	return 0;
}
