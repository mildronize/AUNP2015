#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int	f2c(int fah) {
	return (fah-32)/1.8;
}

int	main(int argc, char **argv) {
	int	cel, fah;

	fah = 32; cel = f2c(fah);
	assert( cel == 0 );
	
	fah = 212; cel = f2c(fah);
	assert( cel == 100);

	return 0;
}
