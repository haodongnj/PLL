#include "fll.h"

void init_fll(fll_s * p, float k_gain_sogi, float gamma, float update_period){
    p->center_freq_radians = 50 * DOUBLE_PI_FLL ;
    p->freq_Hz = 50 ;
    p->freq_radians = 50 * DOUBLE_PI_FLL ;

    p->k_gain_sogi = k_gain_sogi ;
    p->gamma = gamma ;
    p->update_period = update_period ;

    p->sogi_backward_integrator_output = 0 ;
    p->sogi_forward_integrator_output = 0 ;
    p->fll_integrator = 0 ;
} 

float calc_fll(fll_s * p, float pcc_voltage){
    float e, sogi_input, qv, v, temp, ef ;

    e = pcc_voltage - p->sogi_forward_integrator_output ;
    sogi_input = e * p->k_gain_sogi ; 

    qv = p->sogi_backward_integrator_output * p->freq_radians ;

    temp = sogi_input - qv ;

    temp *= p->freq_radians ;
    p->sogi_forward_integrator_output += temp * p->update_period;

    p->sogi_backward_integrator_output += p->sogi_forward_integrator_output * p->update_period;

    ef = e * qv ;

    p->fll_integrator += - p->gamma * ef * p->update_period ;

    p->freq_radians = p->center_freq_radians + p->fll_integrator ;
    p->freq_Hz = p->freq_radians * ONE_OVER_DOUBLE_PI_FLL ;

    return p->freq_Hz ;
}
