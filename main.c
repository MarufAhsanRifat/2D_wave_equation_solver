#include <stdio.h>

int main(void)
{
	printf("Wave solver ready.\n");

	int i;
	double u[10];

	/* Fill with a simple sine profile */
	for (i=0; i<10; i++) {
		u[i] = i*i;
		printf("u[%d] = %.1f \n", i, u[i]);
	}

	return 0;
}
