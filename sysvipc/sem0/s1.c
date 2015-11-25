#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <sys/wait.h>

#define	KEY	0xDEADBEEF

void	child() {
}

void	parent() {
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
		child();
	} else {
		parent();
		wait(NULL);
		fprintf(stderr, "P: all children terminated\n");
	}
	
	return 0;
}
