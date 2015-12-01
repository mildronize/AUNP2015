#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include <sys/wait.h>

#define	BUFSZ	256

#define	KEY	0xDEADBEEF

char	*perm2str(struct ipc_perm p) {
	static char str[BUFSZ];

	sprintf(str, "[k=0x%08X,uid=%d,gid=%d,cuid=%d,cgid=%d,mode=%o,seq=%d]",
		p.__key,
		(int)p.uid,
		(int)p.gid,
		(int)p.cuid,
		(int)p.cgid,
		(int)p.mode,
		p.__seq);

	return str;
}

void	semStatus(int semid) {
	int	ret;
	struct	semid_ds ds;

	ret = semctl(semid, 0, IPC_STAT, &ds);
	if (ret == -1) { perror("semctl"); exit(-1); }
	fprintf(stderr, "t=%ld,sid=%d,otime=%ld,ctime=%ld,nsems=%d,perm:%s\n", 
		(long)time(NULL),
		semid,
		(long)ds.sem_otime, 
		(long)ds.sem_ctime, 
		(int)ds.sem_nsems,
		perm2str(ds.sem_perm)
	);
}

int	semGetSemPid(int semid, int n) {
	int	ret = semctl(semid, n, GETPID);
	if (ret == -1) { perror("semctl"); exit(-1); }
	return ret;
}

int	semGetNCount(int semid, int n) {
	int	ret = semctl(semid, n, GETNCNT);
	if (ret == -1) { perror("semctl"); exit(-1); }
	return ret;
}

int	semGetZCount(int semid, int n) {
	int	ret = semctl(semid, n, GETZCNT);
	if (ret == -1) { perror("semctl"); exit(-1); }
	return ret;
}

int	semGetVal(int semid, int n) {
	int	ret = semctl(semid, n, GETVAL);
	if (ret == -1) { perror("semctl"); exit(-1); }
	return ret;
}

void	child(int semid) {
	struct	sembuf sem;
	int	ret;

	sem.sem_num = 0;
	sem.sem_op = -1;		/* wait for 1 resource */
	sem.sem_flg = SEM_UNDO;
	
	fprintf(stderr,"C: request for semaphore\n");

	semStatus(semid);

	ret = semop(semid, &sem, 1);
	if (ret == -1) { perror("semop"); exit(-1); }

	semStatus(semid);

	fprintf(stderr,"C: got semaphore\n");
}

void	parent(int semid) {
	struct	sembuf sem;
	int	ret;

	sem.sem_num = 0;
	sem.sem_op = 1;		/* Provide resource 1 */
	sem.sem_flg = 0;

	fprintf(stderr,"P: sleep 5 secs\n");
	semStatus(semid);

	sleep(5);

	fprintf(stderr,"P: request for semaphore\n");
	ret = semop(semid, &sem, 1);
	if (ret == -1) { perror("semop"); exit(-1); }
	fprintf(stderr,"P: give semaphore\n");

	semStatus(semid);
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
