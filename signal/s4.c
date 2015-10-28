#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>


void	sighandler(int signo) {
	printf("Got signal %d\n", signo);
}

int	main(void) {
	int	count = 0;
	signal(SIGINT, &sighandler);
	signal(SIGQUIT, &sighandler);
	signal(SIGTERM, &sighandler);
	while (1) {
		printf("count = %d\n", count++);
		sleep(1);
	}
	return 0;
}
