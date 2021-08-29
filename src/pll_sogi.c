#include <pll_sogi.h>
#include <math.h>

/// in case of compiling under MS windows
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


void init_pll_sogi(PLL_SOGI_t *s, float kp, float ki, float dt, float fc){
    s->center_angle_freq = fc * 2 * M_PI;
    s->angle_freq = s->center_angle_freq  ;
    s->update_period = dt;
    s->loop_filter_ki = ki * s->update_period ;
    s->loop_filter_kp = kp ;
    s->phase_output = 0 ;
    s->sogi_backward_integrator_output = 0 ;
    s->sogi_forward_integrator_output = 0 ;
    s->loop_filter_sum = 0 ;
}

float calc_pll_sogi(PLL_SOGI_t *s, float signal){
    float error ;

    error = signal - s->sogi_forward_integrator_output ;
    error -= s->sogi_backward_integrator_output * s->angle_freq ;
    error *= s->angle_freq ;
    s->sogi_forward_integrator_output += error * s->update_period;

    s->sogi_backward_integrator_output += s->sogi_forward_integrator_output * s->update_period;

    error = s->sogi_forward_integrator_output * cos(s->phase_output) +
        s->sogi_backward_integrator_output * s->angle_freq * sin(s->phase_output) ;
    s->loop_filter_sum += error * s->loop_filter_ki ;
    s->angle_freq = s->center_angle_freq + s->loop_filter_sum + s->loop_filter_kp * error ;
    s->phase_output += s->angle_freq * s->update_period ;

    if(s->phase_output > 2 * M_PI){
        s->phase_output -= 2 * M_PI ;
    }

    return s->phase_output ;
}
