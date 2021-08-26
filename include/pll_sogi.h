#ifndef PLL_SOGI_H
#define PLL_SOGI_H

typedef struct PLL_SOGI{
    float sogi_forward_integrator_output ;
    float sogi_backward_integrator_output ;
    float phase_output ;
    float loop_filter_kp ;
    float loop_filter_ki ;
    float angle_freq ;
    float update_period ;
    float center_angle_freq;
    float loop_filter_sum ;

} PLL_SOGI_t;

void init_pll_sogi(PLL_SOGI_t *s, float kp, float ki, float dt, float fc);
float calc_pll_sogi(PLL_SOGI_t *s, float signal) ;

#endif