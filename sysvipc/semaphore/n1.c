/*
 * newspaper stand
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define	PAGESIZE	1

char	*buf;
int	shmid;

#define	NEWSPAPER	(buf[0])
#define	SALE		(buf[1])
#define	ANGRY		(buf[2])
#define	OK		(buf[3])

void sale(int id) {
	int	tmp;

	while (1) {
		fprintf(stderr,	"S[%d] -- customer arrive,"
				"asking for newpaper\n", id);

		tmp=NEWSPAPER;
		
		if (tmp>0) {
			fprintf(stderr,	"S[%d] check, paper left = %d,"
					" You can buy one if you want\n",
					id, tmp);
		} else {
			fprintf(stderr, "S[%d] check, paper left = %d, "
					" Sorry, we don't have it, CUSTOMER OK\n",
					id, tmp);
			OK++;
			sleep(1);
			continue;
		}

		sleep(1);

		if (NEWSPAPER>0) {
			NEWSPAPER--;
			fprintf(stderr, "S[%d] pick up one paper,"
					" paper left = %d\n",
					id, NEWSPAPER);
			SALE++;
		} else {
			fprintf(stderr, "S[%d] say Sorry, no paper left"
					" anymore! CUSTOMER ANGRY!\n",
					id);
			ANGRY++;
		}
		sleep(1);

	}
}

void	cleanup(void) {
	shmdt(buf);
}


int	main(void) {
	int	pid;

	shmid=shmget(	IPC_PRIVATE,
			PAGESIZE,
			0600
		    );
	if (shmid==-1) { perror("shmget"); exit(-1); }

	atexit(cleanup);	/* Cleanup shared memory when finished */

	buf=shmat(	shmid,
			(void *)NULL,
			0
		 );
	if (buf==(void *)-1) { perror("shmat"); exit(-1); }

	if (shmctl(shmid, IPC_RMID, 0)==-1) {
		perror("shmctl:destroy shared mem");
		exit(-1);
	}

	NEWSPAPER=1;
	SALE=0;
	ANGRY=0;
	OK=0;

	pid=fork();
	if (pid==-1) { perror("fork()"); exit(-1); }
	if (pid==0) { /* child */
		sale(1);
	}
	pid=fork();
	if (pid==-1) { perror("fork()"); exit(-1); }
	if (pid==0) { /* child */
		sale(2);
	}

	sleep(1);
	srand(getpid());

	/* Parrent as newspaper supplier */
	while(1) {
		NEWSPAPER++;
		fprintf(stderr, "P:supplier deliver 1 more paper"
				" total paper = %d\n", NEWSPAPER);
		fprintf(stderr,"PAPERLEFT=%d, SALE=%d, OK=%d, ANGRY=%d\n",
				NEWSPAPER, SALE, OK, ANGRY);
		sleep(rand()%4+1);
	}

	return 0;
}
