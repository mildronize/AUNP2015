#include <stdio.h>

struct	info {
	char	*name;
	int	age;
	float	height;
	float	weight;
}	n[10];

int	main(int argc, char **argv) {
	char	name[80];
	int	age;
	float	height, weight;

	while(1) {
		int count=scanf("%s %d %f %f\n", name, &age, &height, &weight);
		if (count!=4) { printf("count = %d\n", count); break; }
		printf("name = %s, age=%3d height=%2.1f weight=%2.1f\n", name, age, height, weight);
	}

	/*
	for (i=0;i<2;i++) {
		printf("%s %3d %2.1f %2.2f\n", n[i].name, n[i].age, n[i].height, n[i].weight);
	}
	*/

	return 0;
}
