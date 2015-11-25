/*
 * sharedmem3.c	Create 'private' shared memory (key=IPC_PRIVATE)
 * 		memory can be shared among parent and children.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define	PAGESIZE	(4096)

char	*buf=(char *)NULL;

int	main(int argc, char *argv[]) {
	int	pid,c;
	int	shmid;

	shmid=shmget(	IPC_PRIVATE,	/* Private Shared Memory */
			PAGESIZE,
			0600		/* Shared between parent/child */
		);
	if (shmid == -1) { perror("shmget"); exit(-1); }
	buf=shmat(	shmid,
			(void *)NULL,	/* Let the system choose */
			0		/* default, Read/Write */
		);

	fprintf(stderr,"Buf address = 0x%X\n", (unsigned int)buf);
	memset(buf,0,sizeof(buf));	/* Clear buffer */
	if (argc!=1) {			/* if called with argument */
		strcpy(buf,argv[1]);	/* Copy it to buffer */
	}

	fprintf(stderr,"forking...\n");
	pid=fork();
	if (pid==-1) { perror("fork()"); exit(-1); }

	if (pid==0) {	/* child increment buf[0] ten times */
		int	i;

		c='C';
		for (i=0;i<3;i++) {
			int	t;

			t=buf[0];	printf("%c:t=buf[0]=%d\n", c, t);
			sleep(1);
			t=t+1;		printf("%c:t++;t=%d\n", c, t);
			sleep(1);
			buf[0]=t;	printf("%c:buf[0]=t=%d\n", c, t);
		}
	} else {
		int	i;
		c='P';

		for (i=0;i<3;i++) {
			int	t;

			t=buf[0];	printf("%c:t=buf[0]=%d\n", c, t);
			sleep(1);
			t=t+1;		printf("%c:t++;t=%d\n", c, t);
			sleep(1);
			buf[0]=t;	printf("%c:buf[0]=t=%d\n", c, t);
		}
	}

	fprintf(stderr,"%c:buf[0]=%d\n",c,buf[0]);

	if (shmdt(buf)==-1) {
		fprintf(stderr,"%c:shared memory at %X detach failed\n",
				c, (int)buf);
		exit(-1);
	}
	
	fprintf(stderr,"%c:shared memory detached\n",c);

	if (pid!=0) {	/* parent handle mark shared mem as destroy */
		wait(NULL);	/* wait for child to terminate */
		if (shmctl(shmid, IPC_RMID, (void *)NULL)==-1) {
			perror("shmctl:IPC_RMID");
			exit(-1);
		}
		fprintf(stderr,"%c:destroy shared memory id=%d\n",
				c, shmid);
	}

	return 0;
}
