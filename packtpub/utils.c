#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <assert.h>

char	*ltrim(char *s) {
	while (isspace(*s)) s++;
	return s;
}

char	lastchar(char *s) {
	int	l=strlen(s);
	return *(s+l-1);
}

char	*rtrim(char *s) {

	while (isspace(lastchar(s))) {
		int l = strlen(s);
		*(s+l-1) = '\0';
	}

	return s;
}

char	*remove_end_h2_tag_at_end_string(char *s) {
	char	tag[]="</h2>\n";
	int	l = strlen(s);
	int	taglen = strlen(tag);

	if (strcmp((s+l-taglen), tag) == 0) {
		*(s+l-taglen) = '\0';
	}
	return s;
}

#ifdef	MAIN
int	main(int argc, char **argv) {
	char	buf[1024], *ptr;
	char	c;

	strcpy(buf, " ABCDEF");
	assert ( strcmp(buf, " ABCDEF")==0 );

	ptr = ltrim(buf);
	assert ( strcmp(ptr, "ABCDEF")==0 );

	strcpy(buf, " \t\t ABCDEF");
	ptr = ltrim(buf);
	assert ( strcmp(ptr, "ABCDEF")==0 );

	strcpy(buf, " \t\n\t");
	ptr = ltrim(buf);
	assert ( strcmp(ptr, "")==0 );

	strcpy(buf, "");
	ptr = ltrim(buf);
	assert ( strcmp(ptr, "")==0 );

	c = lastchar("ABCDEF");
	assert( c == 'F' );

	strcpy(buf, "ABCDEF    ");
	ptr = rtrim(buf);
	assert ( strcmp(ptr, "ABCDEF")==0 );

	strcpy(buf, "ABCDEF</h2>");
	ptr = remove_end_h2_tag_at_end_string(buf);
	assert ( strcmp(ptr, "ABCDEF")==0 );
	
	return 0;
}
#endif
