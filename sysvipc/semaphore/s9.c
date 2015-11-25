/*
 * s9.c
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define	KEYVALUE	(0xABCDEF01)
#define	BUFSIZE		(10*1000*1000)

void	increment(char *buf, unsigned count) {
	unsigned i;

	for (i=0;i<count;i++) { buf[i]++; }
}

void	decrement(char *buf, unsigned count) {
	unsigned i;

	for (i=0;i<count;i++) { buf[i]--; }
}

unsigned sum(char *buf, unsigned count) {
	unsigned i,s=0;

	for (i=0;i<count;i++) { s+=buf[i]; }
	return s;
}

void	usage(char *prog) {
	fprintf(stderr,	"Usage: %s op\n"
			"Where op is '+' for increment\n"
			"	  or '-' for decrement\n"
			"	  or 's' for summation\n",
			prog);
	exit(0);
}

int	main(int argc, char *argv[]) {
	char	op,*buf;
	int	shmid;
	key_t	key=KEYVALUE;

	if (argc!=2) usage(argv[0]);
	op=argv[1][0];
	if (op!='+' && op!='-' && op!='s') usage(argv[0]);

	/* create */
	shmid=shmget(	key,
			BUFSIZE,
			0600 | IPC_CREAT
		    );
	if (shmid==-1) { perror("shmget"); exit(-1); }

	/* attach */
	buf=shmat(	shmid,
			(void *)NULL,
			0
		 );
	if (buf==(void *)-1) { perror("shmat"); exit(-1); }

	/* use it */
	while (1) {
		switch(op) {
		case	'+':
			increment(buf, BUFSIZE);
			fprintf(stderr,"+");
			break;
		case	'-':
			decrement(buf, BUFSIZE);
			fprintf(stderr,"-");
			break;
		case	's':
			fprintf(stderr, "[Sum=%d]\r", sum(buf, BUFSIZE));
			break;
		default:
			break;
		}
	}

	/* detach */
	if (shmdt(buf)==-1) { perror("shmdt"); exit(-1); }

	if (op=='s') {	/* the 'sum' one should destroy the share mem */
		if (shmctl(	shmid,
				IPC_RMID,
				0
		      )==-1) {
			perror("shmctl:destroy");
			exit(-1);
		}
	}
}
