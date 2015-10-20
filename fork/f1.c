#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	child() {
	printf("child end\n");
	exit(0);
}

void	parent() {
	sleep(2);
	printf("parent call pstree\n");
	system("ps u");
}

int	main(void) {
	pid_t	pid;

	pid = fork();
	if (pid == -1) { perror("fork"); exit(-1); }
	if (pid == 0) {	/* child */
		child();
	} else {	/* parent */
		parent();
		wait(NULL);
		printf("parent call pstree after wait()\n");
		system("ps u");
	}

	return 0;
}
