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
char	buf[BUFSIZE];

int	main(void) {
	time_t	t;
	int	br;
	int	*msgtype=buf;

	/* Create message queues */
	msgid=msgget(
			(key_t)KEY,
			0600 | IPC_CREAT
		    );
	if (msgid == -1) { perror("msgget"); exit(-1); }
	memset(buf,0,sizeof(buf));

	t=time(NULL);

	/* Server wait for receiving message from queues */
	while (1) {
		int	i;

		br=msgrcv(
				msgid,		/* Receiving from this queues id */
				buf,		/* Store data into this buff */
				sizeof(buf)-sizeof(int),	/* Max buffer size */
				0,		/* Read from type */
				0 		// | IPC_NOWAIT
			 );
		if (br==-1) { perror("msgrcv"); exit(-1); }
		fprintf(stderr,"Receive %d bytes, message type %d\n",
				br, *msgtype);
		for (i=0;i<br;i++) {
			fprintf(stderr,"%c",(char)*(buf+sizeof(int)+i));
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
