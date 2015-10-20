#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rev.h"
#include "pdot.h"
#include "pdash.h"

int	main(void) {
	char	*s="Hello World";

	printf("%s\n", rev(s));
	printf("%s\n", rev("This is a test"));
	printf("012345678901234567890123456789\n");
	printf("%s\n", rev("This is a test long string."));
	printf("012345678901234567890123456789\n");
	pdot(10);	printf("\n");
	printf("012345678901234567890123456789\n");
	pdash(15);	printf("\n");
	printf("sin(0.7)=%2.3f\n",sin(0.7));
	exit(0);
}
