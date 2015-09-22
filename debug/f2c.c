#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double	f2c(double fah) {
	return (fah-32)/1.8;
}

#ifdef	MAIN
int	main(int argc, char **argv) {
	double	cel, fah;

	fah = 32; cel = f2c(fah);
	assert( cel == 0 );
	
	fah = 212; cel = f2c(fah);
	assert( cel == 100);

	fah = -40; cel = f2c(fah);
	assert( cel == -40);

	return 0;
}
#endif
