/*
 * m1.c
 *
 * message-queue
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define	BUFSIZE	256

int	msgid;
int	pid;

void	child(void) {
	char	buf[BUFSIZE];
	int	i,*msgtype=buf;

	for (i=0;i<10;i++) {
		*msgtype=i+1;
		sprintf(buf+sizeof(int),"Type %d sending at %d",
				*msgtype, time(NULL));
		if (	msgsnd(	msgid, 
				buf,
				strlen(buf+sizeof(int)),
				0
			      )==-1 ) {
			perror("msgsnd"); exit(-1);
		}
		fprintf(stderr,"C: sending message %d, type=%d\n",
				i, *msgtype);
		sleep(1);
	}
	fprintf(stderr,"C: finished sending all messages\n");
}

void	parent(void) {
	char	buf[BUFSIZE];
	int	i;
	long	*msgtype=buf;

	memset(buf,0,sizeof(buf));
	for (i=0;i<10;i++) {
		int	t;

		t=i+1;	/* wait for message queue type i+1 */
		*msgtype = t;
		fprintf(stderr,"P: wait for message type %d\n", t);
		if (	msgrcv(	msgid,
				buf,
				sizeof(buf),
				t,
				0
			      )==-1 ) {
			perror("msgrcv"); exit(-1);
		}
		fprintf(stderr,"P: got [%d], message = '%s'\n",
				*msgtype, buf+sizeof(int));
	}
}

int	main(void) {

	/* create message queue */
	msgid=msgget(
			IPC_PRIVATE,
			0600
		    );

	if (msgid == -1) { perror("msgget"); exit(-1); }
	pid=fork();
	if (pid==-1) { perror("fork"); exit(-1); }
	if (pid==0) {	/* child */
		child();
	} else {	/* parent */
		parent();
		wait(NULL);
		fprintf(stderr,"P: child terminated!\n");

		if (msgctl(msgid, IPC_RMID, (void *)NULL)==-1) {
			perror("msgctl:rmid"); exit(-1);
			exit(-1);
		}
		fprintf(stderr,"P: message queue remove\n");
	}

	return 0;
}

/*
 * end of file.
 */
