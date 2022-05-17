#ifndef INCLUDE_PLL_SOGI_H_
#define INCLUDE_PLL_SOGI_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PLL_SOGI {
  float sogi_forward_integrator_output;
  float sogi_backward_integrator_output;
  float phase_output;
  float loop_filter_kp;
  float loop_filter_ki;
  float ke;
  float angle_freq;
  float update_period;
  float center_angle_freq;
  float loop_filter_sum;

} PLL_SOGI_t;

/**
 * @brief initialize PLL_SOGI_t struct
 *
 * @param s pointer to PLL_SOGI_t struct
 * @param ke gain for error part of SOGI
 * @param kp proportional gain for loop filter of PLL
 * @param ki integrational gain for loop filter of PLL
 * @param dt period for calculation
 * @param fc center frequency in Hz
 */
void init_pll_sogi(PLL_SOGI_t *s, float ke, float kp, float ki, float dt, float fc);

/**
 * @brief calculation of PLL.
 *
 * @param s pointer to PLL_SOGI_t struct
 * @param signal input signal
 * @return float instant calculated phase
 */
float calc_pll_sogi(PLL_SOGI_t *s, float signal);

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_PLL_SOGI_H_
