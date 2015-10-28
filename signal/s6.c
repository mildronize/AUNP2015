#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

void	sighandler(int signo) {
	printf("Got signal %d\n", signo);
}

int	main(void) {
	int	count = 0;

	struct	sigaction oldact, act;

	sigaction(SIGINT, NULL, &oldact);
	act = oldact;
	act.sa_handler = &sighandler;
	sigaction(SIGINT, &act, NULL);
	
	while (1) {
		printf("count = %d\n", count++);
		sleep(1);
	}
	return 0;
}
