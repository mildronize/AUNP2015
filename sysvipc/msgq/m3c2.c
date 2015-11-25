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
	int	ok;
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
		int	i, ret;
		char	c;
		static	int count = 0;	

		if (feof(stdin)) { fprintf(stderr, "stdin:EOF reached\n"); exit(0); }
		if (ferror(stdin)) { fprintf(stderr, "stdin:ERROR\n"); exit(0); }
		fprintf(stderr,"(N,c)> ");
		ret = scanf("%d %c", &i, &c);
		if (ret != 2) {
			fprintf(stderr,"expect number follow by single char ret=%d\n", ret);
			fflush(stdin);
			if (count++ > 10) { exit(0); }
			continue;
		}

		count = 0;
		memset(m.mtext,0,sizeof(m.mtext));
		memset(m.mtext,(int)c,i);

		m.msgtype=1;
		ok=msgsnd(
			msgid,	/* Receiving from this queues id */
			&m,	/* Store data into this buff */
			i, /* size of message */
			0
		);
		if (ok==-1) {
			perror("msgsnd");
//			exit(-1);
		}
	}

	return 0;
}

/*
 * end of file.
 */
