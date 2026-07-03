#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void grid_init(Grid2D *g, int nx, int ny, double dx, double dy) 
{
	int total_rows = nx + 2;	/* including boundary rows */
	int total_cols = ny + 2;	/* including boundary columns */

	g->nx	= nx;
	g->ny	= ny;
	g->dx	= dx;
	g->dy	= dy;
	g->stride = total_cols;

	g->data	= (double *) calloc((size_t)(total_rows * total_cols), sizeof(double)); 

	if (g->data == NULL) {
		fprintf(stderr, "grid_init: calloc failed \n");
		exit(EXIT_FAILURE);
	}
}

void grid_free(Grid2D *g)
{
	free(g->data);
	g->data	= NULL;
	g->nx	= g->ny = 0;
	g->dx	= g->dy = 0.0;
	g->stride = 0;
}

void grid_set_ic(Grid2D *g, ICFunc f)
{
	int i, j;
	for (i = 0; i <= g->nx + 1; i++){
		double x = i * g->dx; 	/* i=0 -> x=0 (boundary) */
		for (j = 0; j <= g->ny + 1; j++){
			double y = j * g->dy;
			*grid_at(g, i, j) = f(x,y);
		}
	}
}

double ic_gaussian(double x, double y)
{
	double r2 = (x - 0.5) * (x - 0.5) + (y - 0.5)*(y - 0.5);
	return exp(-r2 / (0.1 * 0.1));
}

double ic_planar_wave(double x, double y)
{
	/* A sinusoidal wave front propagation along x */
	(void) y;	/* unused */
	return sin(2.0 * M_PI * x);
}
