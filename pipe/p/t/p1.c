#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void) {
	char	cmd[]="ls";
	int	ret;

	ret = system(cmd);
	printf("ret = %d\n", ret);
	return 0;
}
