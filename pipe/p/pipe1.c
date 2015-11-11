/*
 * pipe1.c
 *
 * test pipe() function.
 * parent will write message, child will receive message.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	parent(int fd) {
	char	buf[]="Hello World\n";
	int	i;

	for (i=0;i<strlen(buf);i++) {
		int	r;

		r=write(fd, buf+i, 1);
		if (r==-1) { perror("write"); exit(-1); }
		printf("P:send[%c]\n",buf[i]);
/*		sleep(1);	*/
	}
	close(fd);
	wait(NULL);
	printf("P:child terminated!\n");
}

void	child(int fd) {
	char	c;
	do {
		int	r;

		r=read(fd, &c, 1);
		if (r==-1) { perror("read"); exit(-1); }
		if (r==0) { break; } /* EOF */
		printf("C:rec[%c]\n",c);
	} while (1);
}

int	main(void) {
	int	pid;
	int	fd[2];

	if (pipe(fd)==-1) {
		perror("pipe"); exit(-1);
	}
	pid=fork();
	if (pid==-1) {
		perror("fork"); exit(-1);
	}
	if (pid==0) {	/* Child */
		close(fd[1]);	/* We don't use write end, close it. */
		child(fd[0]);
	} else {	/* parent */
		close(fd[0]);	/* We don't use read end, close it. */
		parent(fd[1]);
	}
	return 0;
}
