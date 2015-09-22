#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rev.h"
#include "pdot.h"
#include "pdash.h"

int	main(void) {
	char	*s="Hello World";
	void	*ptr=&pdot;

	printf("%s\n", rev(s));
	printf("%s\n", rev("This is a test"));
	pdot(80); printf("\n");
	pdash(30); printf("\n");
	printf("addr of pdot=%lx\n", (long int)ptr);
	
	exit(0);
}
