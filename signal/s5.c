#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

void	sighandler(int signo) {
	printf("Got signal %d\n", signo);
}

void	do_something(char *s) {
	int	i;
	for (i=0;i<5;i++) { fprintf(stderr, "do_something: %s %d\n", s, i); sleep(1); }
}

int	main(void) {
	struct	sigaction oldact, act;

	/* ---- signal() ----- */

	signal(SIGINT, SIG_IGN);
	do_something("signal");

/*
	signal(SIGINT, SIG_DFL);
	do_something("after signal()");
*/
	signal(SIGINT, &sighandler);

	/* --- sigaction() ---- */

	sigaction(SIGINT, NULL, &oldact);
	act = oldact;
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);

	do_something("sigaction");

	sigaction(SIGINT, &oldact, NULL);

	do_something("after sigaction()");

	/* end sigaction */
	
	return 0;
}
