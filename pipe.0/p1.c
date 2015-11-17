#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CMD	"find ../. -name \\*.c"

int	main(int argc, char **argv) {
	system(CMD);

	return 0;
}
