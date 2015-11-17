#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int	main(void) {
	FILE	*fp;
	int	i;

	fp=fopen("/tmp/log.txt","w");
	if (fp==NULL) { perror("fopen"); exit(-1); }
	clearerr(fp);
	for (i=0;i<100;i++) {
		char	buf[80];
		int	bw;
		time_t	t;

		t=time(NULL);
		sprintf(buf,"%d",(int)t);
		bw=fwrite(buf,sizeof(char),strlen(buf),fp);
		fprintf(stderr,".");
		if (ferror(fp)) { perror("fwrite"); exit(-1); }
		if (bw!=strlen(buf)) { 
			fprintf(stderr,"[%d] req:%d:write:%d\n",
				i,strlen(buf),bw);
		}
		sleep(1);
	}
	fclose(fp);
	return 0;
}
