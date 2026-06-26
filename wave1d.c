#include <stdio.h>
#include <math.h>

#define NX	100 	// number of interior points + 1 (0 and NX are boundaries)
#define NSTEPS	500
#define C	1.0
#define DX	0.01
#define DT	0.004
#define COEFF	((C*DT/DX)*(C*DT/DX))     // c (dt/dx)^2

int main(void)
{
	double u_prev[NX+1] = {0};
	double u_curr[NX+1] = {0};
	double u_next[NX+1] = {0};
	int i, n;

	// Initial condition: Gaussian pulse at x=0.5
	for (i = 0; i <= NX; i++) {
		double x = i * DX;
		double arg = (x - 0.5) / 0.05; 		// width 0.05
		u_curr[i] = exp(- arg*arg);
	}

	// Set boundaries to zero (fixed ends)
	u_curr[0] = u_curr[NX] = 0.0;
	u_next[0] = u_next[NX] = 0.0;

	// For the first step, use zero initial velocity => u_prev = u_curr
	for (i = 0; i <= NX; i++) u_prev[i] = u_curr[i];

	// Time stepping
	for (n=0; n < NSTEPS; n++) {
		// Update interior points
		for (i = 1; i < NX; i++) {
			u_next[i] = 2.0 * u_curr[i] - u_prev[i] 
				+ COEFF * (u_curr[i+1] - 2.0*u_curr[i] + u_curr[i-1]);
		}
	
		// Print profile every 50 steps
		if (n % 50 == 0) {
			printf("Step %d\n", n);
			for (i = 0; i <= NX; i++) printf("%.4f", u_curr[i]);
		        printf("\n\n");
		}

		// Swap pointers: prev <- curr, curr <- next
		// (We'll use array copying for now; pointer swap comes later when we use dynamic memory)
		for (i = 0; i <= NX; i++) {
			u_prev[i] = u_curr[i];
			u_curr[i] = u_next[i];
		}
	}
	
	return 0;
}
