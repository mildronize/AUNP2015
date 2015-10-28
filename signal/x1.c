#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	f() {
}

void	f2() {
}

int	main(void) {
	printf("f     = %08x\n", (unsigned)f);
	printf("&f    = %08x\n", (unsigned)&f);
	printf("f2    = %08x\n", (unsigned)f2);
	printf("&f2   = %08x\n", (unsigned)&f2);
	printf("main  = %08x\n", (unsigned)main);
	printf("&main = %08x\n", (unsigned)&main);
	return 0;
}
