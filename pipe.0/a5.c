#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv) {
	FILE	*f;
	int	i;
	char	buf[256];

	f = freopen("/etc/passwd", "r", stdin);
/*	f = stdin;	*/
	/* --- */
	fscanf(f, "%s", buf);

	scanf("");
	fscanf(stdin,"");

	fprintf(stdout,"buf=[%s]\n", buf);
	fprintf(stdout, "..."
	return 0;
}
