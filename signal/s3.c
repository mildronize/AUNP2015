#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>


void	sighandler() {
	printf("Got interrupt!");
}

int	main(void) {
	int	count = 0;
	int	i;
	for (i=0;i<256;i++) {
		printf("i=%d\n", i);
		signal(i, &sighandler);
	}
	while (1) {
		printf("count = %d\n", count++);
		sleep(1);
	}
	return 0;
}
