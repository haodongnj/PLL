#ifndef PLL_MATLAB_H
#define PLL_MATLAB_H

#define INIT_PHASE 0.0
#define INIT_FREQ 50.0
#define UG_INIT_PHASE 0.0

// For a input signal of a 1V magnitude ;
#define KP_PLL 120 ;
#define KI_PLL 2800 ;

// For a input signal of 220V magnitude ;
//#define KP_PLL 4 ;
//#define KI_PLL 16 ;

#define PI 3.141592653589793
#define DOUBLE_PI 6.283185307179586
#define TS 1e-4
#define HALF_TS 5e-5
#define SIZE_OF_QUEUE 300

#define FREQ_MAX 55.0
#define FREQ_MIN 45.0

#define A11		0.977912228775521
#define A12		-2.440151404761418
#define A21		0.000098895611439 
#define A22		0.999877992429762

#define B11		0.988956114387761
#define B21		0.000049447805719

#define C11		0.000122007570238  
#define C12		2.467250579465816 

#define D11		6.100378511903545e-05

#define X11		0
#define X21		19.453667259328849




void InitPLL(void);
double UpdatePLL( double UgridSampled);

#endif
