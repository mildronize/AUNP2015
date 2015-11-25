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

#define	BUFSIZE	5000
#define	KEY	(0xFADE)

int	msgid;
char	buf[BUFSIZE];

int	main(void) {
	time_t	t;
	int	br;
	int	count=0;
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

		count++;
		fprintf(stderr,"message to send> ");
		scanf("%s",buf+sizeof(int));
		*msgtype=1;
		br=msgsnd(
			msgid,	/* Receiving from this queues id */
			buf,	/* Store data into this buff */
			strlen(buf+sizeof(int)), /* size of message */
			0
		);
		if (br==-1) { perror("msgsnd"); exit(-1); }
		fprintf(stderr,"Sent %d bytes, message type %d\n",
				br, *msgtype);
		for (i=0;i<br;i++) {
			fprintf(stderr,"%c",(char)*(buf+sizeof(int)+i));
		}
		fprintf(stderr,"\n");
	}

	return 0;
}

/*
 * end of file.
 */
