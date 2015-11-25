#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define	MKEY	0x123456
#define	BUFSZ	128

int	main(int argc, char **argv) {
	int	mid, mtype = 0;
	char	buf[BUFSZ];

	if (argc > 1) {
		if (sscanf(argv[1], "%d", &mtype)>0) {
			fprintf(stderr, "Using message type = %d\n", mtype);
		} else {
			fprintf(stderr, "Hmm expect first argument as int\n");
			exit(-1);
		}
	}
	mid = msgget(MKEY, IPC_CREAT | 0666);
	if (mid == -1) { perror("msgget"); exit(-1); }
	if (mtype == 0) printf("Receive all -- ");
	printf("Message queue is ready\n");

	while(1) {
		int i;
		int sz = msgrcv(mid, buf, sizeof(buf), mtype, 0);
		printf("Got %d bytes\n", sz);
		for (i=0;i<sz;i++) {
			printf(" %02X", buf[i]);
		}
		printf(" [");
		for (i=4;i<sz;i++) {
			printf("%c", buf[i]);
		}
		printf("]\n");
	}
}
