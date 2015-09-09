#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <time.h>

#define	CURLCMD	"curl -s -o free-learning.txt https://www.packtpub.com/packt/offers/free-learning"
#define	FILENAME	"free-learning.txt"
#define	RESULTFILE	"outfile.txt"
#define	BUFSZ	1024

#include "utils.h"

void	saveresult(char *s) {
	FILE *f;
	struct	timeval tv;
	char	tbuf[BUFSZ];

	f=fopen(RESULTFILE, "a+");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	gettimeofday(&tv, NULL);
	strcpy(tbuf, ctime(&tv.tv_sec));
	tbuf[strlen(tbuf)-1] = '\0';
	fprintf(f, "%s\t%s\n", tbuf, s);
	fclose(f);
}


int	main(int argc, char **argv) {
	char	buf[BUFSZ];
	FILE	*f;
	int	count;

	/* if file free-learning.txt is not exist, then get it */
	/* system(CURLCMD);  */
	f = fopen(FILENAME, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	count = 0;
	while(1) {
                char *s = fgets(buf, sizeof(buf), f);
                if (s == (char *)NULL)
                        break;
		if (++count==601) {
			s = ltrim( rtrim( remove_end_h2_tag_at_end_string(buf) ) );
/*			printf("result = '%s'\n", s);	*/
			saveresult(s);
			break;
		}
        }
	if (count != 601) { fprintf(stderr, "failed to get bookname\n"); exit(-1); }
 
	fclose(f);
	
	exit(0);
}

