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

#define	BUFSIZE	0xFFFF

int	msgid = 0;
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

void	clearmsgq() {
	if (msgid != 0 ) {
		if (msgctl(msgid, IPC_RMID, (void *)NULL)==-1) {
			perror("msgctl:rmid"); exit(-1);
			exit(-1);
		}
		fprintf(stderr,"message queue remove\n");
	}
}

void	child(void) {
	int	success = 0;
	int	size = 8200;
	int	ret, total=0;

	m.msgtype = 1;
	sprintf(m.mtext ,"Type %ld sending at %s",
			m.msgtype, now());
	
	while (total < 8000) {
		int	sz = sizeof(m.msgtype) + strlen(m.mtext);
		ret = msgsnd(	msgid, &m, sz, 0);
		if (ret == -1) {
			printf("failed\n");
			exit(-1);
		} else {
			printf("send = %ld bytes\n", sizeof(m.msgtype) + strlen(m.mtext));
			total += sz;
		}
	}
	
	while (!success) {
		if (	msgsnd(	msgid, 
				&m,
				size,
				0
			      )==-1 ) {
			printf("failed at size = %d\n", size);
			size--;
		} else {
			success = 1;
			printf("success at size = %d\n", size);
		}
	}
	printf("Sizeof m.msgtype = %ld\n", sizeof(m.msgtype));
	fprintf(stderr,"C: sending message type=%ld\n", m.msgtype);
}

void	parent(void) {
	sleep(5);
	memset(m.mtext,0,sizeof(m.mtext));
	fprintf(stderr,"P: wait for message type 1\n");
	while (1) {
		if (	msgrcv(	msgid,
				&m,
				sizeof(m),
				0,
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
		atexit(clearmsgq);

		parent();
		wait(NULL);
		fprintf(stderr,"P: child terminated!\n");
	}

	return 0;
}

/*
 * end of file.
 */
