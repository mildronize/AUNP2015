/*
 * m3s.c
 *
 * message-queue, the server
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

#define	BUFSIZE	20000
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
	int	br;
	struct	msgbuf m;

	/* Create message queues */
	msgid=msgget(
			(key_t)KEY,
			0600 | IPC_CREAT
		    );
	if (msgid == -1) { perror("msgget"); exit(-1); }
	memset(m.mtext,0,sizeof(m.mtext));

	/* Server wait for receiving message from queues */
	while (1) {
		int	i;

		br=msgrcv(
				msgid,		/* Receiving from this queues id */
				&m,		/* Store data into this buff */
				sizeof(m.mtext),	/* Max buffer size */
				0,		/* Read from type */
				0 		// | IPC_NOWAIT
			 );
		if (br==-1) { perror("msgrcv"); exit(-1); }
		fprintf(stderr,"Receive %d bytes, message type %ld\n",
				br, m.msgtype);
		for (i=0;i<br;i++) {
			fprintf(stderr,"%c",m.mtext[i]);
		}
		fprintf(stderr,"\n");
	}

	/* Destroy message queues */
	if (msgctl(
			msgid,
			IPC_RMID,
			(void *)NULL
		  )==-1) {
			perror("msgctl:rmid"); exit(-1);
	}

	return 0;
}

/*
 * end of file.
 */
