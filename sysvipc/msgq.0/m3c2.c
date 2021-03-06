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
char	buf[BUFSIZE];

int	main(void) {
	time_t	t;
	int	br;
	int	*msgtype=buf;

	/* Create message queues */
	msgid=msgget(
			(key_t)KEY,
			0600
		    );
	if (msgid == -1) { perror("msgget"); exit(-1); }
	memset(buf,0,sizeof(buf));

	t=time(NULL);

	/* Server wait for receiving message from queues */
	while (1) {
		int	i;
		char	c;

		fprintf(stderr,"(N,c)> ");
		if (scanf("%d %c", &i, &c)!=2) {
			fprintf(stderr,"expect number follow by single char\n");
			continue;
		}
		memset(buf,0,sizeof(buf));
		memset(buf+sizeof(int),(int)c,i);

		*msgtype=1;
		br=msgsnd(
			msgid,	/* Receiving from this queues id */
			buf,	/* Store data into this buff */
			i, /* size of message */
			0
		);
		if (br==-1) { perror("msgsnd"); }
	}

	return 0;
}

/*
 * end of file.
 */
