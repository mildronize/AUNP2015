/*
 * two-pipe1.c
 *
 * two pipe for two-way communications
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void	convert(char *,int);
time_t	tStart;

#define	BUFSZ	256

void	parent(int rfd,int wfd) {
	while(1) {
		int	count,len;
		char	buf[BUFSZ+1];

		memset(buf,0,sizeof(buf));	/* Clear buffer */
		printf("enter> ");		/* Read data from terminal */
		fgets(buf,BUFSZ,stdin);

		/* prepare the data */
		len=strlen(buf);
		if (buf[len]=='\n') { buf[len]='\0'; }

		/* send it to the child process */
		count=write(wfd,buf,strlen(buf));
		if (count==-1) { perror("parent:write"); exit(-1); }
		if (count!=strlen(buf)) {
			fprintf(stderr,"parent:write not complete (%d/%d)\n",
					count,strlen(buf));
		}

		count=read(rfd,buf,sizeof(buf));
		if (count==-1) { perror("parent:read"); exit(-1); }
		printf("receive>[%s]\n",buf);
	}

	close(wfd);
	close(rfd);
}

void	child(int rfd,int wfd) {
	do {
		char	buf[BUFSZ+1];
		int	count,count2;

		/* Reading from reading-pipe */
		count=read(rfd,buf,sizeof(buf));
		if (count==-1) { perror("child:read"); exit(-1); }
		if (count==0) { break; }
		buf[count]='\0';		/* terminate it */

		/* Process the data */
		convert(buf,count);

		/* Wrting to writing-pipe */
		count2=write(wfd,buf,count);
		if (count2==-1) { perror("child:write"); exit(-1); }
	} while (1);

	close(rfd);
	close(wfd);
}

/* data processing */
void	convert(char *buf,int len) {
	int	i;

	for (i=0;i<len;i++) {
		if (islower(buf[i])) {
			buf[i]=toupper(buf[i]);
		}
	}
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
		close(c2p[0]);/* close reading end of child-to-parent pipe */
		child(p2c[0],c2p[1]);	/* reading,writing */
	} else {	/* parent */
		close(p2c[0]);	/* close reading end of parent-to-child pipe */
		close(c2p[1]);	/* close writing end of child-to-parent pipe */
		parent(c2p[0],p2c[1]);	/* reading,writing */
	}
	return 0;
}
