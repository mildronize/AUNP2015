#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	CMD	"wc -c -w"

int	main(int argc, char **argv) {
	FILE	*f;
	int	i;

	f = freopen("/etc/passwd", "r", stdin);

	system(CMD);
	
	return 0;
}
