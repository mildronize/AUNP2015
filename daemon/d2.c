#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define	COUNTCMD	"who | cut -f1 -d' ' | wc -l > /tmp/count-temp.txt"
#define	DATECMD		"date > /tmp/date-temp.txt"
#define	FILENAME	"/tmp/count-temp.txt"
#define	FILENAME2	"/tmp/date-temp.txt"

int	count_user(void) {
	FILE	*f;
	int	count;

	system(COUNTCMD);

	f = fopen(FILENAME, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
	fscanf(f, "%d", &count);
	fclose(f);

	return count;
}

char	*datestr(void) {
	FILE	*f;
	static	char	str[80];

	system(DATECMD);

	f = fopen(FILENAME2, "r");
	if (f == (FILE *)NULL) { perror("fopen"); exit(-1); }
/*	fscanf(f, "%s", str);	*/
	fgets(str, sizeof(str), f);
	str[strlen(str)-1] = '\0';

	fclose(f);

	return str;
}

int	main(void) {
	char	*date;
	int	count;
	
	while(1) {
		count = count_user();
		date = datestr();
		printf("%s %d\n", date, count);
		sleep(1);
	}
}
