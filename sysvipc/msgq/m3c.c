/*
 * m3c.c
 *
 * message-queue, the client
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

#define	BUFSIZE	5000
#define	KEY	(0xFADE)

int	msgid;
int	pid;

struct	msgbuf {
	long	msgtype;
	char	mtext[BUFSIZE];
};

char	*now() {
	time_t	t = time(NULL);
	static char buf[BUFSIZE];
	char	*p;

	strncpy(buf, ctime(&t), sizeof(buf));
	p = index(buf, '\n');
	*p = '\0';
	return buf;
}

int	main(void) {
	int	ok;
	int	count=0;
	struct	msgbuf m;

	/* Create message queues */
	msgid=msgget(
			(key_t)KEY,
			0600
		    );
	if (msgid == -1) { perror("msgget"); exit(-1); }
	memset(m.mtext,0,sizeof(m.mtext));

	/* Server wait for receiving message from queues */
	while (1) {
		count++;
		fprintf(stderr,"message to send> ");
		scanf("%s",m.mtext);
		m.msgtype=1;
		ok=msgsnd(
			msgid,	/* Receiving from this queues id */
			&m,	/* Store data into this buff */
			strlen(m.mtext), /* size of message */
			0
		);
		if (ok==-1) { perror("msgsnd"); exit(-1); }
		fprintf(stderr,"Sent, message type %ld, '%s'\n", m.msgtype, m.mtext);
	}

	return 0;
}

/*
 * end of file.
 */
