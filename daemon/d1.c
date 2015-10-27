#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <time.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>

#define	CMD	"who | cut -f1 -d' ' | wc -l > count"
#define	COUNT	"count"
#define	LOG	"log.txt"
#define	BUFSZ	80

int	child() {
	FILE	*f;
	struct	timeval tv;
        char    tbuf[BUFSZ];
	int	count;
 
	while(1) {
		system(CMD);
		f = fopen(COUNT, "r");
		if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
		fscanf(f, "%d", &count);
		fclose(f);

	        gettimeofday(&tv, NULL);
		strcpy(tbuf, ctime(&tv.tv_sec));
		tbuf[strlen(tbuf)-1] = '\0';

		f = fopen(LOG, "a");
		if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
		fprintf(f, "%s\t%d\n", tbuf, count);
		fclose(f);
	}
}

int	main(int argc, char **argv) {
	int	pid;
	int	daemon = 0;

	if (argc == 2) {
		if (strncmp(argv[1], "-d", 2)==0) {
			daemon = 1;
			fprintf(stderr, "set daemon mode\n");
		}
	}

	pid = fork();
	if (pid == -1) { perror("fork"); exit(-1); }
	if (pid == 0) {
		fprintf(stderr, "child pid = %d\n", getpid());
		child();
	} else {
		if (!daemon) {
			wait(NULL);
			fprintf(stderr, "all children terminated\n");
		}
		exit(0);
	}
	return 0;
}
