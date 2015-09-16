#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <dlfcn.h>

#include "rev.h"
#include "pdot.h"
#include "pdash.h"

int	main(void) {
	void	(*my_pdot)(int);
	
	void	*handle;
	handle = dlopen("/home/chatchai.j/2014/2014-09-16/libtest/libp.so", RTLD_LAZY);
	if(!handle) {
		printf("error = %s\n", dlerror());
		exit(-1);
	}

	my_pdot = dlsym(handle, "pdot");
	if (dlerror() != NULL) {
		perror("dlsym");
		exit(-1);
	}

	my_pdot(10);	printf("\n");

	/* pdash(15);	printf("\n");*/
	exit(0);
}
