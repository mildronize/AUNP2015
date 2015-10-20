
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void) {
	char	buf[80];

	int ret;
	printf("before fork() pid=%d ppid=%d\n",getpid(),getppid());
	ret = fork();

	if (ret == -1) { perror("fork"); exit(-1); }
	if (ret == 0) {	/* child */
		printf("c: Child\n");
		printf("c: after fork() pid=%d ppid=%d\n",getpid(),getppid());
	} else {	/* parent */
		printf("p: Parent\n");
		printf("p: my child pid=%d\n",ret);
	}

	return 0;
}
