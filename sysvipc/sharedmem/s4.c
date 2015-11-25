/*
 * s4.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define	PAGESIZE	(4096)

int	main(int argc, char *argv[]) {
	int	shmid;			/* Share memory ID */
	key_t	key=0x1234;		/* Share key */
	char	*buf;
	char	tmp[256];
	struct	shmid_ds ds;

	if (argc==2) {
		if (sscanf(argv[1], "%d", &key)==1) {
			printf("key=%d\n", (int)key);
		} else {
			fprintf(stderr, "usage: %s key_id\n", argv[0]);
			exit(0);
		}
	}
	/* Create */
	fprintf(stderr,"Create share memory with key %d\n", (int)key);
	shmid=shmget(		key,			/* key */
				PAGESIZE,		/* size */
				0600 | IPC_CREAT
		);
	if (shmid==-1) { perror("shmget"); exit(-1); }
	fprintf(stderr,"Get share memory id=%d\n", shmid);

	/* Attached */
	buf=shmat(	shmid,
			(void *)NULL,
			0			/* default read/write */
		);
	if (buf==(void *)-1) { perror("shmat"); exit(-1); }
	fprintf(stderr,"%d:Attached to shared mem at %X\n", getpid(), (int)buf);
	memset(buf,0,PAGESIZE);			/* fill with NULL */

	while (1) {
		if (buf[0]!=0 && strcmp(tmp,buf)!=0) {
			fprintf(stderr,"%d:buf[]='%s'\n",
				getpid(), buf);
			strcpy(tmp,buf);
			if (strcmp(buf,"quit")==0) { break; }
		}
		if (shmctl(shmid, IPC_STAT, &ds)==-1) {
			perror("shmctl"); exit(-1);
		}
		fprintf(stderr,	"size=%d,atime=%d,dtime=%d,ctime=%d,"
				"creator=%d,lastop=%d,nattach=%d\n",
				ds.shm_segsz, 
				(int)ds.shm_atime, 
				(int)ds.shm_dtime, 
				(int)ds.shm_ctime, 
				(int)ds.shm_cpid,
				(int)ds.shm_lpid,
				(int)ds.shm_nattch
			);
		sleep(1);
	}

	/* Detached */
	if (shmdt(buf)==-1) { perror("shmdt"); exit(-1); }

	/* Mark as destroy */
	if (shmctl(	shmid, 				/* ID */
			IPC_RMID,			/* Mark as destroyed */
			(void *)NULL			/* Not used */
		)==-1) {
		perror("shmctl"); exit(-1);
	}

	return 0;
}
