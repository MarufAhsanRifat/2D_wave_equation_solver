#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * We'll store a (NX+2) x (NY+2) array.
 * Boundary rows/columns are at i=0, i=NX+1, j=0, j=NY+1.
 * Interior: i=1...NX, j=1...ny.
 */

#define NX 50
#define NY 50
#define DX 0.02
#define DY 0.02

/* Flattened index macro: row-major order */
#define IDX(i, j, ny) ((i) * (ny) + (j) )

int main(void) 
{
	int nx2 = NX + 2;	/* total points in x-direction */
	int ny2 = NY + 2; 	
	double *grid;

	/* Allocate one contiguous block of doubles */
	grid = (double *) malloc((size_t)(nx2 * ny2) * sizeof(double)); 
	if (grid == NULL) {
		fprintf(stderr, "Error: malloc failed \n");
		return EXIT_FAILURE;
	}

	/*
	 * Alternative: calloc initialises memory to zero.
	 * grid = (double *) calloc((size_t)(nx2 * ny2), sizeof(double));
	 */

	/* Initialise with a Gaussian bump */
	int i, j;
	for (i = 0; i < nx2; i++) {
		for (j = 0; j < ny2; j++) {
			double x = i * DX;	/* i=0 is boundary */
			double y = j * DY; 
			double arg = ((x-0.5)*(x-0.5) + (y-0.5)*(y-0.5))/ (0.1 * 0.1);
			grid[IDX(i, j, ny2)] = exp(-arg);
		}
	}

	/* Print a horizontal slice at j = NY/2 (approx middle) */
	int mid = NY / 2;
	printf("Slice at j=%d (y=%.2f): \n", mid, mid*DY);
	for (i = 0; i < nx2 ; i++) {
		printf(" u[%d][%d] = %8.4f\n", i, mid, grid[IDX(i, mid, ny2)]);
	}
	
	/* Free memory */
	free(grid);

	printf("\nAllocation and free successful.\n");
	return 0;
}
