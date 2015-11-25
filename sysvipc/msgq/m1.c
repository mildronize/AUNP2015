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
#include <sys/time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define	BUFSIZE	256

int	msgid;
int	pid;

struct	msgbuf {
	long	msgtype;
	char	mtext[BUFSIZE];
} m;

char	*now() {
	time_t	t = time(NULL);
	static char buf[BUFSIZE];
	char	*p;

	strncpy(buf, ctime(&t), sizeof(buf));
	p = index(buf, '\n');
	*p = '\0';
	return buf;
}

void	child(void) {
	int	i;

	for (i=0;i<10;i++) {
		m.msgtype = i + 1;
		sprintf(m.mtext ,"Type %ld sending at %s",
				m.msgtype, now());
		if (	msgsnd(	msgid, 
				&m,
				strlen(m.mtext)+sizeof(m.msgtype),
				0
			      )==-1 ) {
			perror("msgsnd"); exit(-1);
		}
		fprintf(stderr,"C: sending message %d, type=%ld\n",
				i, m.msgtype);
		sleep(1);
	}
	fprintf(stderr,"C: finished sending all messages\n");
}

void	parent(void) {
	int	i;

	memset(m.mtext,0,sizeof(m.mtext));
	for (i=0;i<10;i++) {
		int	t;

		t=i+1;	/* wait for message queue type i+1 */
		fprintf(stderr,"P: wait for message type %d\n", t);
		m.msgtype = t;
		if (	msgrcv(	msgid,
				&m,
				sizeof(m),
				t,
				0
			      )==-1 ) {
			perror("msgrcv"); exit(-1);
		}
		fprintf(stderr,"P: got [%ld], message = '%s'\n",
				m.msgtype, m.mtext);
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
