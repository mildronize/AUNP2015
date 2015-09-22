#include <stdio.h>
#include <unistd.h>
#include <math.h>

int	main(void) {
	float x = 3.14159/4;
	float y;
	
	while (1) {
		y = sin(x);
		sleep(10);
		x = y+x;
	}

	return 0;
}
