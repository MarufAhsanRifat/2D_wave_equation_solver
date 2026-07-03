#include <stdio.h>
#include "grid.h"

int main(void)
{
	Grid2D g;
	grid_init(&g, 20, 20, 0.05, 0.05);

	/* Fill with Gaussian initial conditions */
	grid_set_ic(&g, ic_gaussian);

	/* Print centre slice */
	int mid = g.ny / 2;
	printf("Slice at j=%d (y=%.3f):\n", mid, mid*g.dy);
	for (int i = 0; i <= g.nx + 1; i++){
		printf(" u[%d][%d] = %8.4f\n", i, mid, *grid_at(&g, i, mid));
	}

	/* Test alternative IC */
	grid_set_ic(&g, ic_planar_wave);
	printf("\nPlanar wave at i=5 (x=%.3f): \n", 5*g.dx);
	for (int j = 0; j <= g.ny + 1; j++){
		printf("%8.4f ", *grid_at(&g, 5, j));
	}
	printf("\n");

	grid_free(&g);
	printf("\nGrid freed successfully. \n");
	return 0;
}
