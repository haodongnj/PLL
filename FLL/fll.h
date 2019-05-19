#ifndef PLL_SOGI_H
#define PLL_SOGI_H 

#define DOUBLE_PI_FLL 6.283185307179586
#define ONE_OVER_DOUBLE_PI_FLL 0.1591549430918953478495424044098

typedef struct fll_s{
    float k_gain_sogi ;
    float gamma ;
    float sogi_forward_integrator_output ;
    float sogi_backward_integrator_output ;
    float update_period ;
    float freq_radians ;
    float center_freq_radians ; 
    float freq_Hz ;
    float fll_integrator ;
} fll_s ;

void init_fll(fll_s * p, float k_gain_sogi, float gamma, float update_period); 
float calc_fll(fll_s * p, float pcc_voltage) ;

#endif