#ifndef GRID_H
#define GRID_H

#include <stddef.h>	/* size_t */

typedef struct {
	double *data;	/* flattened 2-D array (row-major) */
	int	nx;	/* number of interior points in x */
	int 	ny;	/* number of interior points in y */
	double 	dx; 	/* grid spacing in x */
	double 	dy;	/* grid spacing in y */
	int 	stride;	/* total columns = ny + 2, for index calculations */
} Grid2D;

/* Initialisation functions - signature */
void grid_init(Grid2D *g, int nx, int ny, double dx, double dy);
void grid_free(Grid2D *g);

/* Inline index helper - placed in header for inlining  */
static inline double* grid_at(Grid2D *g, int i, int j){
	return &g->data[i * g->stride + j];
}

/* Initial condition functions (prototypes) */
typedef double (*ICFunc)(double x, double y);
void grid_set_ic(Grid2D *g, ICFunc f);

/* Some built-in ICs */
double ic_gaussian(double x, double y);
double ic_planar_wave(double x, double y);

#endif	/* GRID_H  */
