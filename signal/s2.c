#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <signal.h>

int	main(void) {
	int	count = 0;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	while (count < 30) {
		printf("count = %d\n", count++);
		sleep(1);
	}
	return 0;
}
