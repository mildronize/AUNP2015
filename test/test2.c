#include <stdio.h>

#ifndef	BUFSZ
#define	BUFSZ	2048
#endif

char	buf[BUFSZ];

int	main(void) {
	printf("Size of buf = %ld\n", sizeof(buf));
	return 0;
}
