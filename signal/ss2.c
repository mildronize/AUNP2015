#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

int	child(void) {
	int	count = 0;
	int	i;

/*
	for (i=0;i<100;i++) {
		signal(i, SIG_IGN);
	}
*/

	while (count < 30) {
		printf("count = %d\n", count++);
		sleep(1);
	}
	return 0;
}

int	main(void) {
	int	pid = fork();

	if (pid == -1) { perror("fork()"); exit(-1); }
	if (pid == 0) {
		child();
	} else {		/* parent */
		printf("this is parent pid=%d, cpid=%d\n", getpid(), pid);
		sleep(40);
	}

}
