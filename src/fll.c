#include <fll.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_1_PI
#define M_1_PI 0.31830988618379067153803535746773
#endif

void init_fll(FLL_t *s, float k_gain_sogi, float gamma, float dt, float fc){
    s->center_freq_radians = fc * 2 * M_PI;
    s->freq_Hz = fc ;
    s->freq_radians = fc * 2 * M_PI;

    s->k_gain_sogi = k_gain_sogi ;
    s->gamma = gamma ;
    s->update_period = dt;

    s->sogi_backward_integrator_output = 0 ;
    s->sogi_forward_integrator_output = 0 ;
    s->fll_integrator = 0 ;
} 

float calc_fll(FLL_t *s, float signal){
    float e, sogi_input, qv, v, temp, ef ;

    e = signal - s->sogi_forward_integrator_output ;
    sogi_input = e * s->k_gain_sogi ;

    qv = s->sogi_backward_integrator_output * s->freq_radians ;

    temp = sogi_input - qv ;

    temp *= s->freq_radians ;
    s->sogi_forward_integrator_output += temp * s->update_period;

    s->sogi_backward_integrator_output += s->sogi_forward_integrator_output * s->update_period;

    ef = e * qv ;

    s->fll_integrator += - s->gamma * ef * s->update_period ;

    s->freq_radians = s->center_freq_radians + s->fll_integrator ;
    s->freq_Hz = s->freq_radians * M_1_PI;

    return s->freq_Hz ;
}
