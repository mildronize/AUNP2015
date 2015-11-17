/*
 * p-stdio3.c
 *
 * test pipe() function.
 * Parent(P) will write message, Child(C) will receive message.
 * Changing from file descriptor (int fd) to file pointer (FILE *fp).
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

time_t	tstart;

/* The parent process */
void	parent(FILE *fp) {
	time_t	t;
	int	i;

	char	*s[80] = {
		"Hello World.",
		"How are you doing?",
		"I'm fine, thank you, and you?"
	};
	
	/* Loop sending the message */
	for (i=0;i<3;i++) {
		t=time(NULL) - tstart;
		fprintf(fp,"%s",s[i]); fflush(fp);
		fprintf(stderr,"P:%d:Send[%s]\n",(int)t,s[i]);
		sleep(1);
	}

	/* Finish sending, waiting a few seconds before closing pipe */
	t=time(NULL) - tstart;
	fprintf(stderr,"P:%d:wait for 3 secs before close(fp) ",(int)t);
	for (i=0;i<3;i++) { fprintf(stderr,"."); sleep(1); }
	fprintf(stderr,"\n");

	/* Close pipe */
	fclose(fp);
	t=time(NULL) - tstart;
	fprintf(stderr,"P:%d:close(fp)\n",(int)t);

	/* Wait for child to terminate */
	wait(NULL);
	t=time(NULL) - tstart;
	printf("P:%d:child terminated!\n",(int)t);
}

/* The child process */
void	child(FILE *fp) {
	time_t	t;
	char	buf[80];
	int	i;

	do {
		/* Read the data from pipe, if no more data then break loop */
		if(fgets(buf, sizeof(buf), fp)==NULL) { break; }

		/* If get the data, the printing it out immediately */
		t=time(NULL) - tstart;
		fprintf(stderr,"C:%d:rec[%s]\n",(int)t,buf);
	} while (1);

	/* No more data */
	t=time(NULL) - tstart;
	fprintf(stderr,"C:%d:nothing more to read\n",(int)t);

	/* Waiting for a few second before terminate */
	t=time(NULL) - tstart;
	fprintf(stderr,"C:%d:Wait for 3 seconds before I terminated ",(int)t);
	for (i=0;i<3;i++) { fprintf(stderr,"."); sleep(1); }
	fprintf(stderr,"\n");
}

/* The main program */
int	main(void) {
	int	pid;
	int	fd[2];

	if (pipe(fd)==-1) {
		perror("pipe"); exit(-1);
	}
	tstart=time(NULL);
	pid=fork();
	if (pid==-1) {
		perror("fork"); exit(-1);
	}
	if (pid==0) {	/* Child */
		FILE *fp;
		close(fd[1]);	/* We don't use write end, close it. */
		fp=fdopen(fd[0],"r");
		if (fp==NULL) { perror("fdopen"); exit(-1); }

		setbuf(fp,NULL);
		child(fp);
	} else {	/* parent */
		FILE *fp;
		close(fd[0]);	/* We don't use read end, close it. */
		fp=fdopen(fd[1],"w");
		if (fp==NULL) { perror("fdopen"); exit(-1); }

		setbuf(fp,NULL);
		parent(fp);
	}
	return 0;
}
