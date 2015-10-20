#include <stdio.h>

int	f() {
	static int	i;

	printf("i=%d\n", i++);
	return i;
}

int	main(void) {
	int x=f();
	printf("x=%d\n", x);
	x=f();
	printf("x=%d\n", x);
}
