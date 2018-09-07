#include "pll_sogi.h"

void init_pll_sogi(pll_sogi_s * p, double kp, double ki, double update_period){
    p->center_angle_freq = 50 * DOUBLE_PI_PLL_SOGI ;
    p->angle_freq = p->center_angle_freq  ;
    p->update_period = update_period ;
    p->loop_filter_ki = ki * p->update_period ;
    p->loop_filter_kp = kp ;
    p->phase_output = 0 ;
    p->sogi_backward_integrator_output = 0 ;
    p->sogi_forward_integrator_output = 0 ;
    p->loop_filter_sum = 0 ;
} 

double calc_pll_sogi(pll_sogi_s * p, double pcc_voltage){
    double error ;

    error = pcc_voltage - p->sogi_forward_integrator_output ;
    error -= p->sogi_backward_integrator_output * p->angle_freq ;
    error *= p->angle_freq ;
    p->sogi_forward_integrator_output += error * p->update_period;

    p->sogi_backward_integrator_output += p->sogi_forward_integrator_output * p->update_period;

    error = p->sogi_forward_integrator_output * cos(p->phase_output) + 
        p->sogi_backward_integrator_output * p->angle_freq * sin(p->phase_output) ;
    p->loop_filter_sum += error * p->loop_filter_ki ;
    p->angle_freq = p->center_angle_freq + p->loop_filter_sum + p->loop_filter_kp * error ;
    p->phase_output += p->angle_freq * p->update_period ;

    if(p->phase_output > DOUBLE_PI_PLL_SOGI){
        p->phase_output -= DOUBLE_PI_PLL_SOGI ;
    }

    return p->phase_output ;
}
