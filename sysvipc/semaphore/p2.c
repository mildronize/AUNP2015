/*
 * philosopher
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define	MAXHUNGER	(10)

int	semid;
struct	sembuf	sop;

void think(void) { sleep(1); }
void eat(void)	{ sleep(1); }


void philosopher(int id) {
	int	hungry = 0;
	time_t	t;

	while (1) {

		t=time(NULL);
		fprintf(stderr, "p[%d] request for 2 forks\n", id);
		sop.sem_op = -2;
		if (semop(semid, &sop, 1)==-1) { perror("semop"); exit(-1); }

		fprintf(stderr, "p[%d] I have two forks after waiting for %d, "
				"I'm going to eat now\n", 
				id, (int)(time(NULL) - t));

		eat(); 
		hungry=0;
		fprintf(stderr,"p[%d] finish eating, I'm full...\n", id);
		fprintf(stderr,"p[%d] return two forks at %d\n", id, (int)(time(NULL) - t));
		sop.sem_op = 2;
		if (semop(semid, &sop, 1)==-1) { perror("semop"); exit(-1); }
		fprintf(stderr,"p[%d] thinking...\n",id);
		think();

		fprintf(stderr,"p[%d] I'm hungry now\n", id);
	}
}

#define	PAGESIZE	1

int	main(void) {
	int	pid;

	/* Semaphore */
	semid=semget(	IPC_PRIVATE,
			1,		/* We need only 1 resource here */
			0600
		    );
	if (semid==-1) { perror("semget"); exit(-1); }

	sop.sem_num=0;          /* 1st resource */
	sop.sem_op=3;           /* only 1 resource */
	sop.sem_flg=SEM_UNDO;   /* System will undone when process exit */

	if (semop(semid, &sop, 1)==-1) { 
		perror("semop"); 
		exit(-1); 
	}

	pid=fork();
	if (pid==-1) { perror("fork()"); exit(-1); }
	if (pid==0) { /* child */
		philosopher(1);
	}
	pid=fork();
	if (pid==-1) { perror("fork()"); exit(-1); }
	if (pid==0) { /* child */
		philosopher(2);
	}
	philosopher(3);

	return 0;
}
