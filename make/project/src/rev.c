#include <string.h>
#include <rev.h>

char	*rev(char *str) {
	int	l, i;
	static	char buf[REVBUFSZ];

	l = strlen(str);
	if (l>REVBUFSZ) l=REVBUFSZ;
	memset(buf, 0, REVBUFSZ);
	for (i=0;i<l;i++)
		buf[i] = str[l-i-1];
	return buf;
}

