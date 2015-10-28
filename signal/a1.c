#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <sys/time.h>

void	sighandler(int signo) {
	struct timeval t1,t2;
	static char c;
	int	i;
	
	if (signo == SIGINT) {
		c = 'I';
	} else if (signo == SIGUSR1) {
		c = '1';
	} else if (signo == SIGUSR2) {
		c = '2';
	}

	gettimeofday(&t1, NULL);
	fprintf(stderr, "Got signal %d\n", signo);
	for (i=0;i<3;i++) {
		fprintf(stderr, "%c", c);
		sleep(1);
	}
	gettimeofday(&t2, NULL);
	fprintf(stderr, "signal %d ENDED [%d]->[%d]\n", signo, (int)t1.tv_sec, (int)t2.tv_sec);
	return;
}

int	main(void) {
	int	count = 0;
	signal(SIGINT, &sighandler);
	signal(SIGUSR1, &sighandler);
	signal(SIGUSR2, &sighandler);

	while (1) {
		printf("count = %d\n", count++);
		sleep(1);
	}
	return 0;
}
