
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void) {
	char	buf[80];

	int ret;
	sprintf(buf, "This is the string");
	printf("value in buf='%s'\n", buf);

	printf("before fork() pid=%d ppid=%d\n",getpid(),getppid());
	ret = fork();

	if (ret == -1) { perror("fork"); exit(-1); }
	if (ret == 0) {	/* child */
		printf("c: Child wait for 10 seconds\n");
		sleep(10);
	} else {	/* parent */
		printf("p: Parent set string\n");
		sprintf(buf, "Parent new string");
	}

	printf("%c: value in buf='%s'\n", (int)(ret==0?'c':'p'), buf);
	printf("%c: after fork() pid=%d ppid=%d ret=%d\n",
			(int)(ret==0?'c':'p'),
			getpid(),getppid(),ret);

	if (ret != 0) { 
		int status;
		printf("p: wait\n");
		wait(&status); 
		if (WIFEXITED(status)) {
			printf("p: child terminated normally\n");
		} else {
			printf("p: child die horribly\n");
		}
	}
	return 0;
}
