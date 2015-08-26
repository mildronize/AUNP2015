#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int	c2f(int cel) {
	return cel*1.8+32;
}

#ifdef	MAIN
int	main(int argc, char **argv) {
	int	cel, fah;

	cel = 0; fah = c2f(cel);
	assert( fah == 32);
	
	cel = 100; fah = c2f(cel);
	assert( fah == 212);

	return 0;
}
#endif
