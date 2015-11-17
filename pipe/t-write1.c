#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

int	main(void) {
	int	fd;
	int	i;

	fd=open("/tmp/log.txt",O_WRONLY,0644);
	if (fd==-1) { perror("open"); exit(-1); }
	for (i=0;i<100;i++) {
		char	buf[80];
		int	bw;
		time_t	t;

		t=time(NULL);
		sprintf(buf,"%d",(int)t);
		bw=write(fd,buf,strlen(buf));
		fprintf(stderr,".");
		if (bw==-1) { perror("write"); exit(-1); }
		if (bw!=strlen(buf)) { 
			fprintf(stderr,"[%d] req:%d:write:%d\n",
				i,strlen(buf),bw);
		}
		sleep(1);
	}
	close(fd);
	return 0;
}
