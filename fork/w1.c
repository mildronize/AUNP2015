#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void) {
	int	cpid;

	cpid = fork();
	if (cpid == -1) { perror("fork"); exit(-1); }
	if (cpid == 0) {	/* child process */
		printf("C: sleep 10 secs\n");
		execl("/bin/sleep","/bin/sleep","10",NULL);
	} else {		/* parent process */
		int	status;
		waitpid(cpid, &status, 0);
		printf("P: child %d is terminated\n", cpid);
	}
	return 0;
}
