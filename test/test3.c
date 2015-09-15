#include <stdio.h>

#ifndef	BUFSZ
#define	BUFSZ	2048
#endif

char	buf[BUFSZ];

int	main(void) {
	int	i;

	for (i=0;i<sizeof(buf);i++) {
		buf[i]=i+1;
	}
	printf("Size of buf = %ld\n", sizeof(buf));
	return 0;
}
