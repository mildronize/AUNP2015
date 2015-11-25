#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <sys/wait.h>

#define	KEY	0xDEADBEEF

void	child(int semid) {
	struct	sembuf sem;
	int	ret;

	sem.sem_num = 0;
	sem.sem_op = -1;		/* wait for 1 resource */
	sem.sem_flg = SEM_UNDO;
	
	fprintf(stderr,"C: request for semaphore\n");
	ret = semop(semid, &sem, 1);
	if (ret == -1) { perror("semop"); exit(-1); }
	fprintf(stderr,"C: got semaphore\n");
}

void	parent(int semid) {
	struct	sembuf sem;
	struct	semid_ds ds;
	int	ret;

	ret = semctl(semid, 0, IPC_STAT, &ds);
	if (ret == -1) { perror("semctl"); exit(-1); }
	fprintf(stderr, "otime=%ld, ctime=%ld,nsems=%d\n", 
		(long)ds.sem_otime, (long)ds.sem_ctime, ds.sem_nsems);

	sem.sem_num = 0;
	sem.sem_op = 1;		/* Provide resource 1 */
	sem.sem_flg = 0;

	fprintf(stderr,"P: sleep 5 secs\n");
	sleep(5);
	fprintf(stderr,"P: request for semaphore\n");
	ret = semop(semid, &sem, 1);
	if (ret == -1) { perror("semop"); exit(-1); }
	fprintf(stderr,"P: give semaphore\n");
}

int	main(int argc, char **argv) {
	int	semid;
	int	pid;
	int	ret;
	struct	sembuf sem;

	semid = semget(IPC_PRIVATE, 1, 0600);
	if (semid == -1) { perror("semget"); exit(-1); }

	sem.sem_num = 0;
	sem.sem_op = 0;		/* wait for zero */
	sem.sem_flg = 0;

	ret = semop(semid, &sem, 1);
	if (ret == -1) { perror("semop"); exit(-1); }
	fprintf(stderr, "Wait for Zero, semop() return\n");

	pid = fork();
	if (pid == -1) { perror("fork"); exit(-1); }
	if (pid == 0) {
		child(semid);
	} else {
		parent(semid);
		wait(NULL);
		fprintf(stderr, "P: all children terminated\n");
	}
	
	return 0;
}
