#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/time.h>

#define	HOME		"/home/a2015"

/*
#define	FILENAME	HOME "/tmp/count-temp.txt"
#define	FILENAME2	HOME "/tmp/date-temp.txt"
#define	FILENAME3	HOME "/tmp/outfile.txt"
#define	COUNTCMD	"who | cut -f1 -d' ' | wc -l > " FILENAME
#define	DATECMD		"date > " FILENAME2
*/

#define	BUFSZ	128
char	FILENAME[BUFSZ];
char	FILENAME2[BUFSZ];
char	FILENAME3[BUFSZ];
char	COUNTCMD[BUFSZ];
char	DATECMD[BUFSZ];

int	count_user(void) {
	FILE	*f;
	int	count;

	system(COUNTCMD);

	f = fopen(FILENAME, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	fscanf(f, "%d", &count);
	fclose(f);

	return count;
}

char	*datestr(void) {
	FILE	*f;
	static	char	str[80];

	system(DATECMD);

	f = fopen(FILENAME2, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
/*	fscanf(f, "%s", str);	*/
	fgets(str, sizeof(str), f);
	str[strlen(str)-1] = '\0';

	fclose(f);

	return str;
}

void	save2file(char *filename, char *str) {
	FILE	*f;

	f = fopen(filename, "a");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	fprintf(f, "%s\n", str);
	fclose(f);
}

int	logdaemon(void) {
	char	*date;
	int	count;
	char	buf[80];

	struct	timeval	t1,t2;

	gettimeofday(&t1, NULL);
	
	while(1) {
		count = count_user();
		date = datestr();
		sprintf(buf, "%s %d", date, count);
		save2file(FILENAME3, buf);
/*		sleep(1);	*/
		
		gettimeofday(&t2, NULL);
		if (t2.tv_sec - t1.tv_sec > 2) {
			exit(0);
		}
	}
}

int	main(void) {
	pid_t	pid;
	pid_t	mypid;

	mypid = getpid();

	sprintf(FILENAME, HOME "/tmp/count-temp.%d.txt", mypid);
	sprintf(FILENAME2, HOME "/tmp/date-temp.%d.txt", mypid);
	sprintf(FILENAME3, HOME "/tmp/outfile.%d.txt", mypid);
	sprintf(COUNTCMD, "who | cut -f1 -d' ' | wc -l > %s", FILENAME);
	sprintf(DATECMD,  "date > %s", FILENAME2);

	pid=fork();
	if (pid == -1) { perror("fork"); exit(-1); }
	if (pid == 0) {	/* child process */
		logdaemon();
	} else {	/* parent process */
		printf("Child process id = %d\n", pid);
	}
	return 0;
}
