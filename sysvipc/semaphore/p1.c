/*
 * philosopher
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define	MAXHUNGER	(10)

char	*buf;
#define	FORK	(buf[0])

void think(void) { sleep(1); }
void eat(void)	{ sleep(1); }


void philosopher(int id) {
	int	hungry = 0;

	while (1) {
		while (FORK==0) { /* no fork left */
			fprintf(stderr,	"p[%d] I have no fork,"
					" waiting ..\n", id);
			hungry++;
			if (hungry == MAXHUNGER) {
				fprintf(stderr, "p[%d] I'm dying..,"
						"no fork in my hand\n", id);
				exit(-1);
			}
			sleep(1);
		}
		FORK--;
		while (FORK==0) { /* no fork left */
			fprintf(stderr, "p[%d] I have only 1 fork,"
					"waiting ...\n", id);
			hungry++;
			if (hungry == MAXHUNGER) {
				fprintf(stderr, "p[%d] I'm dying..,"
						"one fork in my hand\n", id);
				exit(-1);
			}
			sleep(1);
		}
		FORK--;
		fprintf(stderr, "p[%d] I have two forks, "
				"I'm going to eat now\n", id);

		eat(); 
		hungry=0;
		fprintf(stderr,"p[%d] finish eating, I'm full...\n", id);
		FORK++;
		fprintf(stderr,"p[%d] I have drop first fork\n", id);
		FORK++;
		fprintf(stderr,"p[%d] I have drop second fork\n", id);
		fprintf(stderr,"p[%d] thinking...\n",id);
		think();

		fprintf(stderr,"p[%d] I'm hungry now\n", id);
	}
}

#define	PAGESIZE	1

int	main(void) {
	int	pid;
	int	shmid;

	shmid=shmget(	IPC_PRIVATE,
			PAGESIZE,
			0600
		    );
	if (shmid==-1) { perror("shmget"); exit(-1); }

	buf=shmat(	shmid,
			(void *)NULL,
			0
		 );
	if (buf==(void *)-1) { perror("shmat"); exit(-1); }

	FORK=3;

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
