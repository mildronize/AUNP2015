#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct	info {
	char	*name;
	int	age;
	float	height;
	float	weight;
}	n[10];

char	filename[]="input.txt";

int	main(int argc, char **argv) {
	char	name[80];
	int	i, count;
	int	age;
	float	height, weight;

	FILE	*f = fopen(filename, "r");
	if (f==(FILE *)NULL) {
		perror("fopen"); exit(-1);
	}

	while(1) {
		int r=fscanf(f, "%s %d %f %f\n", name, &age, &height, &weight);
		if (r!=4) { printf("r = %d\n", r); break; }
		printf("name = %s, age=%3d height=%2.1f weight=%2.1f\n", name, age, height, weight);
		strcpy(n[count].name, name);
		n[count].age = age; n[count].height = height; n[count].weight = weight;
		count++;
	}

	fclose(f);

	for (i=0;i<count;i++) {
		printf("%s %3d %2.1f %2.2f\n", n[i].name, n[i].age, n[i].height, n[i].weight);
	}

	return 0;
}
