
#include <stdio.h>                                                    
#include <math.h>                                                     
#include <time.h>                                                     
#include "stringlib.h"                                                
#include "read_cfg_file.h"
#include "init_positions.h"
#include "force_energy_calc.h"

// Declare Subroutines                                                

// Declare Global Variables

static double kB = 1.9872041E-3; // actually R in units of kcal/mol/K

//Main Program                                                        

int main() {
	
	// variable declaration for reading config file
	
	char trajFileName[1024];  	// output trajectory file name
	char logFileName[1024];   	// log file name
	
	double temp;    		// temperature
	int nAtoms; 			// Number of atoms

	int nIter;      		// number of MC iterations
	int deltaWrite; 		// how often to write coordinates and log info in MC
	double cutoff2;			// nonbonding interaction cutoff distance squared (Angstrom^2)
	int reevalvel;			// number of steps between reevaluation of velocities...
	int ig;				// random number for velocity initialization

	double Ar_eps;			// epsilon parameter for LJ energy calculation
	double Ar_sigma6;		// sigma^6 for quick LJ energy calculation...

	double kBT;

	int i;

	// variable declaration for initializing particle positions, velocities

	double box; 			// cubic box dimension

	double **coord;			// variable declaration for the coordinates of particles array

//	double **atomVelocities;	// variable declaration for the velocities of particles array

	// variable declaration for force and energy values 

	double **component;

	double **atomForces;		// variable declaration for force acting on atom array

	double Tot_potential_en;	// total potential energy of the system


	// read config data from standard in
	read_cfg_file(trajFileName, logFileName, &temp, &nAtoms, &nIter, &deltaWrite, &reevalvel, &ig, &Ar_eps, &Ar_sigma6, &cutoff2); 
	
	kBT = kB*temp;			// solve for kB*T value
	printf("kB*T = %f\n", kBT);	// Print kB*T value to log file;

	// Array declaration

	coord = (double**) malloc(nAtoms*sizeof(double*));		// allocate coordinate array memory
	
	component = (double**) calloc(3, sizeof(double*));		//allocate memory for the component analysis array...

	atomForces = (double**) calloc(nAtoms,sizeof(double*));		// allocate forces array memory
	
//	atomVelocities = (double**) malloc(nAtoms,sizeof(double*));	// allocate velocity array memory

	for (i=0; i<nAtoms;i++) {
		coord[i] = (double*) malloc(3*sizeof(double));
		atomForces[i] = (double*) malloc(3*sizeof(double));
//		atomVelocities[i] = (double*) malloc(3*sizeof(double));
	}

	// initialize particle positions
	init_positions(coord,nAtoms,&box);

	// need to initialize the velocities for each particle... 

	Tot_potential_en = force_energy_calc(nAtoms, box, cutoff2, Ar_eps, Ar_sigma6, coord, atomForces, component);

	printf("Initial Total potential energy = %f\n", Tot_potential_en);


}

// Subroutines





