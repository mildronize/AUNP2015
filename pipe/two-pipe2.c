/*
 * two-pipe1.c
 *
 * two pipe for two-way communications
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

time_t	tStart;

void	parent(int rfd,int wfd) {
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

void	child(int rfd,int wfd) {
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
	int	p2c[2];	/* Parent to child pipe */
	int	c2p[2];	/* Child to parent pipe */

	if (pipe(p2c)==-1) { perror("pipe"); exit(-1); }
	if (pipe(c2p)==-1) { perror("pipe"); exit(-1); }

	tStart=time(NULL);
	pid=fork();
	if (pid==-1) { perror("fork"); exit(-1); }

	if (pid==0) {	/* Child */
		close(p2c[1]);	/* close writing end of parent-to-child pipe */
		close(c2p([0]));/* close reading end of child-to-parent pipe */
		child(p2c[0],c2p[1]);	/* reading,writing */
	} else {	/* parent */
		close(p2c[0]);	/* close reading end of parent-to-child pipe */
		close(c2p[1]);	/* close writing end of child-to-parent pipe */
		parent(c2p[0],p2c[1]);	/* reading,writing */
	}
	return 0;
}
