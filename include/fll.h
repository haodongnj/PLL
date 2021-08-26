#ifndef FLL_H
#define FLL_H

typedef struct FLL{
    float k_gain_sogi ;
    float gamma ;
    float sogi_forward_integrator_output ;
    float sogi_backward_integrator_output ;
    float update_period ;
    float freq_radians ;
    float center_freq_radians ; 
    float freq_Hz ;
    float fll_integrator ;
} FLL_t;

void init_fll(FLL_t *s, float k_gain_sogi, float gamma, float dt, float fc);
float calc_fll(FLL_t *s, float signal) ;

#endif