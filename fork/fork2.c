#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	int ret;
	printf("before fork() pid=%d ppid=%d\n",getpid(),getppid());
	ret = fork();
	printf("after fork() pid=%d ppid=%d ret=%d\n",getpid(),getppid(),ret);
	sleep(1);
	return 0;
}
