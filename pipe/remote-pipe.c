/*
 * remote execute command via pipe
 * child will receive command from parent
 * execute command using popen, and send output back to parent
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define	BUFSZ	1024

time_t	tStart;

void	parent(int rfd,int wfd) {
	while (1) {
		char	cmd[BUFSZ];
		char	*ptr;

		fprintf(stdout, "$ ");
		ptr = fgets(cmd, sizeof(cmd), stdin);
		if (ptr == (char *)NULL) {
			fprintf(stderr, "No input command, terminated\n");
			exit(0);
		}

		if (
			strncmp(ptr, "quit", strlen("quit")) == 0 ||
			strncmp(ptr, "exit", strlen("exit")) == 0 ) {
			fprintf(stderr, "Good bye world\n");
			kill(0, SIGTERM);
			exit(0);
		}

		fprintf(stderr, "The command '%s' is not supported yet\n", ptr);
	}
}

void	child(int rfd,int wfd) {
	time_t	t;
	int	i;

	do {
		char	buf[256];
		int	br;

		br=read(rfd,buf,sizeof(buf));
		if (br==-1) { perror("read"); exit(-1); }
		if (br==0) { break; }
		buf[br]='\0';		/* terminate it */

		t=time(NULL) - tStart;
		fprintf(stderr,"C:%d:rec[\"%s\"]\n",(int)t,buf);

	} while (1);
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
