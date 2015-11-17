/*
 * pipe0.c
 *
 * test pipe() function.
 * parent will write message, child will receive message.
 * using fdopen to change from file descriptor to file pointer.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void	parent(int fd) {
	FILE *fp;

	printf("parent:use %d\n",fd);
	fp=fdopen(fd,"w");
	if (fp==(FILE *)NULL) { perror("parent:fdopen"); exit(-1); }
	if(setvbuf(fp,NULL,_IONBF,0)!=0) {
		perror("setvbuf"); exit(-1);
	}
	while (1) {
		char	buf[80];
		printf("P> ");
		memset(buf,0,sizeof(buf));	/* fill buf with NULL */
		fgets(buf,sizeof(buf),stdin);	/* read string to buf */
		fprintf(fp,buf);		/* send to child */
		fprintf(fp,"\n");
		if (strncmp(buf,"quit",4)==0) {
			printf("P:fclose(fp)\n");
			if (fclose(fp)==EOF) { perror("fclose"); exit(-1); }

			printf("P:waiting child to terminated\n");
			if(wait(NULL)==-1) {
				perror("parent:wait");
				exit(-1);
			} else {
				printf("Child is terminated! Good bye.\n");
				exit(0);
			}
		}
	}
}

void	child(int fd) {
	FILE	*fp;
	int	c;

	printf("child:use %d\n",fd);
	fp=fdopen(fd,"r");
	if (fp==(FILE *)NULL) { perror("child:fdopen"); exit(-1); }
	if(setvbuf(fp,NULL,_IONBF,0)!=0) {	/* Set Non buffering */
		perror("setvbuf"); exit(-1);
	}
	do {
		c=fgetc(fp);
		if (c!=EOF) {
			if (c!='\n') {
				putchar(c+1);
			} else {
				putchar(c);
			}
		} else {
			printf("child:terminated\n");
			exit(0);
		}
	} while(1);
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
