#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/* #include <sys/wait.h>	*/

void	child() {
	sleep(10);
	system("pstree");
	exit(0);
}

void	parent() {
	system("pstree");
	exit(0);
}

int	main(void) {
	pid_t	pid;

	pid = fork();
	if (pid == -1) { perror("fork"); exit(-1); }
	if (pid == 0) {	/* child */
		child();
	} else {	/* parent */
		parent();
	}

	return 0;
}
