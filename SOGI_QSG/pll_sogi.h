#ifndef PLL_SOGI_H
#define PLL_SOGI_H 

#include "math.h"

#define DOUBLE_PI_PLL_SOGI 6.283185307179586

typedef struct pll_sogi_s{
    double sogi_forward_integrator_output ;
    double sogi_backward_integrator_output ;
    double phase_output ;
    double loop_filter_kp ;
    double loop_filter_ki ;
    double angle_freq ;
    double update_period ;
    double center_angle_freq ; 
    double loop_filter_sum ;

} pll_sogi_s ;

void init_pll_sogi(pll_sogi_s * p, double kp, double ki, double update_period); 
double calc_pll_sogi(pll_sogi_s * p, double pcc_voltage) ;

#endif