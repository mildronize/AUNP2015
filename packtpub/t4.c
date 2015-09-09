#include <stdio.h>

int	main(void) {
	char	c;
	c='B';

	printf("c = '%c', c='%d'\n", c, c);
	if (c < 67 && c > 65) { printf("compare int\n"); }
	if (c < 'C' && c > 'A') { printf("compare char\n"); }
	return 0;
}
