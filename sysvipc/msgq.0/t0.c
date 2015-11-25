#include <stdio.h>

char	b[8];

void	print_b(void) {
	int	i;

	for (i=0;i < sizeof(b);i++) { printf("%02X",(unsigned char)b[i]); }
	printf("\n");
}

int	main(void) {
	int	i;
	int	*j=b;

	memset(b,0,sizeof(b));
	for (i=0;i<10;i++) {
		*j=2<<i; print_b();
	}
	*j=0x1234; print_b();
	*j=0x12345678; print_b();
}
