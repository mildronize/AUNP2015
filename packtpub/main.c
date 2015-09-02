#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define	WGETCMD	"wget https://www.packtpub.com/packt/offers/free-learning"

int	main(int argc, char **argv) {
	system(WGETCMD);
	exit(0);
}

