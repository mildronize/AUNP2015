#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double	c2f(double cel) {
	return cel*1.8+32;
}

#ifdef	MAIN
int	main(int argc, char **argv) {
	double	cel, fah;

	cel = 0; fah = c2f(cel);
	assert( fah == 32);
	
	cel = 100; fah = c2f(cel);
	assert( fah == 212);

	cel = -40; fah = c2f(cel);
	assert( fah == -40);

	return 0;
}
#endif
