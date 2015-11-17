/*
 * pipe2.c
 *
 * test pipe() function.
 * parent will write message, child will receive message.
 * with delay between sending each character.
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
	int	i=0;

/*
	for (i=0;i<strlen(buf);i++) {
		int	r;

		r=write(fd, buf+i, 1);
		if (r==-1) { perror("write"); exit(-1); }
		printf("P:send[%c]\n",buf[i]);
		sleep(1);	
	} */
	while (1) {
		int	r;

		r=write(fd, buf, 1);
		if (r==-1) {
			fprintf(stderr, "Error: r=%d\n", r);
			break;
		}
		fprintf(stderr,"sent %d bytes\n", i++);

		if (i>500000) break;
	}
	fprintf(stderr,"P: parent done, closing fd\n");
	close(fd);
	fprintf(stderr,"P: wait for child to terminated\n");
	wait(NULL);
	printf("P:child terminated!\n");
}

void	child(int fd) {
	char	c;
	int	i;

	for (i=0;i<10;i++) { fprintf(stderr, "."); sleep(1); }
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
