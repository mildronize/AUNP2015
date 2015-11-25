#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define	MKEY	0x123456
#define	BUFSZ	128

int	main(int argc, char **argv) {
	int	mid, mtype = 0;
	char	buf[BUFSZ];
	long	*l = (long*)buf;

	if (argc > 1) {
		if (sscanf(argv[1], "%d", &mtype)>0) {
			fprintf(stderr, "Using message type = %d\n", mtype);
		} else {
			fprintf(stderr, "Hmm expect first argument as int\n");
			exit(-1);
		}
	}

	mid = msgget(MKEY, 0666);
	if (mid == -1) { perror("msgget"); exit(-1); }

	while(1) {
		int len;
		bzero(buf, sizeof(buf));
		printf("> ");
		fgets(buf+4, sizeof(buf) - 5, stdin);
		len = strlen(buf+4);
		printf("Send: '%s'\n", buf+4);
		*l = mtype;
		if (msgsnd(mid, buf, len+4, 0)==-1) {
			perror("msgsnd"); 
		}
	}
}
