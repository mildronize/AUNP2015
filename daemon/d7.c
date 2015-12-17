#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>

#define	HOME		"/home/mildronize"
#define	BUFSZ	128

#define	PENDINGLOG	HOME "/tmp/pending-log.txt"

/*
	USR1 -> everage of session since daemon stated.
	USR2 -> maximum number of session + time since daemon started.
*/

int	SigUSR1 = 0;
int	SigUSR2 = 0;

void	sighandler(int sig) {
	char	buf[BUFSZ];
    struct timeval t;
	sprintf(buf, "Sig %d -- %d.%d\n", sig, (int)t.tv_sec,(int)t.tv_usec);
	if (sig == SIGUSR1) {
		if (SigUSR1 == 0)
			SigUSR1 = 1;
		else save2file(PENDINGLOG, buf);
	} else if(sig == SIGUSR2) {
		if (SigUSR2 == 0)
			SigUSR2 = 1;
		else save2file(PENDINGLOG, buf);
	}
}

char	COUNTTEMP[BUFSZ];
char	DATETEMP[BUFSZ];
char	OUTFILE[BUFSZ];
char	COUNTCMD[BUFSZ];
char	DATECMD[BUFSZ];
char	AVGFILE[BUFSZ];
char	MAXFILE[BUFSZ];

int	count_user(void) {
	FILE	*f;
	int	count;

	system(COUNTCMD);

	f = fopen(COUNTTEMP, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	fscanf(f, "%d", &count);
	fclose(f);

	return count;
}

char	*datestr(void) {
	FILE	*f;
	static	char	str[80];

	system(DATECMD);

	f = fopen(DATETEMP, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
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

void	log_average(struct timeval start, unsigned long sum) {
	struct	timeval now;
	char	buf[BUFSZ];
	unsigned	sec;
	double	avg;

	gettimeofday(&now, NULL);
	sec = now.tv_sec - start.tv_sec;
	avg = (double)sum / sec;
	sprintf(buf, "%d : %lf", (int)now.tv_sec, avg);

	save2file(AVGFILE, buf);
}

void	log_maximum(struct timeval start, unsigned int max) {
	struct timeval now;
	char	buf[BUFSZ];
	unsigned	sec;
	double	avg;

	gettimeofday(&now, NULL);
	sprintf(buf, "%d : T(%d), %d", (int)now.tv_sec, (int)start.tv_sec, max);
    printf("print max\n");
	save2file(MAXFILE, buf);
}

int	logdaemon(void) {
	char	*date;
	int	count, maximum=0;
	unsigned long sum=0;
	char	buf[80];

	struct	timeval	t1,t2;

	gettimeofday(&t1, NULL);

	while(1) {
		count = count_user();
		date = datestr();
		sprintf(buf, "%s %d", date, count);
		save2file(OUTFILE, buf);

		sum += count;
		if (count > maximum) { maximum = count; }

		if (SigUSR1 == 1) {
			log_average(t1, sum);
			SigUSR1 = 0;
		}

		if (SigUSR2 == 1) {
			log_maximum(t1, maximum);
			SigUSR2 = 0;
		}

		sleep(1);
	}
}

int	main(void) {
	pid_t	pid;
	pid_t	mypid;

	mypid = getpid();

	sprintf(COUNTTEMP, HOME "/tmp/count-temp.%d.txt", mypid);
	sprintf(DATETEMP, HOME "/tmp/date-temp.%d.txt", mypid);
	sprintf(OUTFILE, HOME "/tmp/outfile.%d.txt", mypid);
	sprintf(AVGFILE, HOME "/tmp/avg.%d.txt", mypid);
	sprintf(MAXFILE, HOME "/tmp/max.%d.txt", mypid);

	sprintf(COUNTCMD, "who | cut -f1 -d' ' | wc -l > %s", COUNTTEMP);
	sprintf(DATECMD,  "date > %s", DATETEMP);

	pid=fork();
	if (pid == -1) { perror("fork"); exit(-1); }
	if (pid == 0) {	/* child process */
		struct	sigaction usr1,usr2,oldusr1,oldusr2;

		sigaction(SIGUSR1, NULL, &oldusr1);
		sigaction(SIGUSR2, NULL, &oldusr2);
		usr1 = oldusr1;
		usr2 = oldusr2;
		usr1.sa_handler = sighandler;
		usr2.sa_handler = sighandler;
		sigaction(SIGUSR1, &usr1, NULL);
		sigaction(SIGUSR2, &usr2, NULL);

		logdaemon();


	} else {	/* parent process */
		printf("Child process id = %d\n", pid);
	}
	return 0;
}
