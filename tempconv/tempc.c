#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "tempc.h"

int	tempc(double temp_in, char temp_in_unit, double *temp_out, char temp_out_unit) {
	double	t_out;

	if (temp_in_unit == 'c') {
		t_out = c2f(temp_in);
	} else if (temp_in_unit == 'f') {
		t_out = f2c(temp_in);
	} else {
		fprintf(stderr, "Temperature unit '%c' is not supported yet\n", temp_in_unit);
		return -1;
	}

	printf("input = %lf %c, output = %lf %c\n",
			temp_in, temp_in_unit,
			t_out, temp_out_unit);

	*temp_out = t_out;
	return 0;
}

int	main(int argc, char **argv) {
	double	temp_in, temp_out;
	char	temp_in_unit, temp_out_unit;

	temp_in = -40;	temp_in_unit = 'c'; temp_out_unit = 'f';
	tempc(temp_in, temp_in_unit, &temp_out, temp_out_unit);
	assert( temp_out == -40 );

	temp_in = 0;	temp_in_unit = 'c'; temp_out_unit = 'f';
	tempc(temp_in, temp_in_unit, &temp_out, temp_out_unit);
	assert( temp_out == 32 );

	temp_in = 100;	temp_in_unit = 'c'; temp_out_unit = 'f';
	tempc(temp_in, temp_in_unit, &temp_out, temp_out_unit);
	assert( temp_out == 212 );

	temp_in = -40;	temp_in_unit = 'f'; temp_out_unit = 'c';
	tempc(temp_in, temp_in_unit, &temp_out, temp_out_unit);
	assert( temp_out == -40 );

	temp_in = 32;	temp_in_unit = 'f'; temp_out_unit = 'c';
	tempc(temp_in, temp_in_unit, &temp_out, temp_out_unit);
	assert( temp_out == 0 );

	temp_in = 212;	temp_in_unit = 'f'; temp_out_unit = 'c';
	tempc(temp_in, temp_in_unit, &temp_out, temp_out_unit);
	assert( temp_out == 100 );
	return 0;
}
