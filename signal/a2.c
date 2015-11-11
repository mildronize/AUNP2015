#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>
#include <sys/time.h>

sigset_t	pending_sig;

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
	sigemptyset(&pending_sig);
	for (i=0;i<3;i++) {
		if (sigpending(&pending_sig)==-1) {
			perror("sigpending"); exit(-1);
		}
		fprintf(stderr, "[%c%c%c]%c\n",
			sigismember(&pending_sig, SIGINT)==1?'I':' ',
			sigismember(&pending_sig, SIGUSR1)==1?'1':' ',
			sigismember(&pending_sig, SIGUSR2)==1?'2':' ',
			c);
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
