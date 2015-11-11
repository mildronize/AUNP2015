/*
 * pipe3.c
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
#include <time.h>

time_t	tStart;

void	parent(int fd) {
	time_t	t;
	int	i;
	char	*s[80]= {
		"Hello World.",
		"How are you doing?",
		"Fine, thank you, and you?"
	};

	sleep(1);
	for (i=0;i<3;i++) {
		int	bw;

		t=time(NULL) - tStart;
		bw=write(fd,s[i],strlen(s[i]));
		if (bw==-1) { perror("write"); exit(-1); }
		if (bw!=strlen(s[i])) {
			fprintf(stderr,"P:%d:send(\"%s\"):%d\n",(int)t,s[i],bw);
		} else {
			fprintf(stderr,"P:%d:Send(\"%s\")\n",(int)t,s[i]);
		}
		sleep(1);
	}

	/* Finish sending, waiting a few seconds before closing pipe */
	t=time(NULL) - tStart;
	fprintf(stderr,"P:%d:wait for 3 secs before close(fd) ",(int)t);
	for (i=0;i<3;i++) { fprintf(stderr,"."); sleep(1); }
	fprintf(stderr,"\n");

	/* Close pipe */
	close(fd);
	t=time(NULL) - tStart;
	fprintf(stderr,"P:%d:close(fd)\n",(int)t);

	/* Wait for child to terminate */
	wait(NULL);
	t=time(NULL) - tStart;
	printf("P:%d:child terminated!\n",(int)t);
}

void	child(int fd) {
	time_t	t;
	int	i;

	do {
		char	buf[256];
		int	br;

		br=read(fd,buf,sizeof(buf));
		if (br==-1) { perror("read"); exit(-1); }
		if (br==0) { break; }
		buf[br]='\0';		/* terminate it */

		t=time(NULL) - tStart;
		fprintf(stderr,"C:%d:rec[\"%s\"]\n",(int)t,buf);

	} while (1);

	/* No more data */
	t=time(NULL) - tStart;
	fprintf(stderr,"C:%d:nothing more to read\n",(int)t);

	/* Waiting for a few second before terminate */
	t=time(NULL) - tStart;
	fprintf(stderr,"C:%d:Wait for 3 seconds before I terminated ",(int)t);
	for (i=0;i<3;i++) { fprintf(stderr,"."); sleep(1); }
	fprintf(stderr,"\n");
}

int	main(void) {
	int	pid;
	int	fd[2];

	if (pipe(fd)==-1) {
		perror("pipe"); exit(-1);
	}
	tStart=time(NULL);
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
