/* file init_old_coord.c */
// c code for the init_old_coord subroutine

#include <math.h>
#include "init_old_coord.h"

void init_old_coord(int nAtoms, double delta_t, double **atomVelocities, double **coord, double **old_coord) {

	int atom1;
	int j;

	for(atom1=0;atom1<nAtoms;atom1++) {
		for(j=0;j<3;j++) {
			old_coord[atom1][j] = coord[atom1][j] - delta_t*atomVelocities[atom1][j];
		}
	}
}

