#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

void	printcur() {
	struct rlimit r;

	if (getrlimit(RLIMIT_MSGQUEUE, &r)==-1) {
		perror("getrlimit"); exit(-1);
	}
	printf("curlimit = %d, maxlimit = %d\n", (int)r.rlim_cur, (int)r.rlim_max);
}

void	setnew(int newval) {
	struct rlimit r;

	r.rlim_cur = newval;

	if (setrlimit(RLIMIT_MSGQUEUE, &r)==-1) {
		perror("setrlimit"); exit(-1);
	}
	printf("curlimit = %d, maxlimit = %d\n", (int)r.rlim_cur, (int)r.rlim_max);
}


int	main(void) {
	printcur(); setnew(81920);
	printcur(); setnew(81920*2);
	printcur(); setnew(819200+1);
	printcur();

	return 0;
}
