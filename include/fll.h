#ifndef INCLUDE_FLL_H_
#define INCLUDE_FLL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FLL {
    float k_gain_sogi;
    float gamma;
    float sogi_forward_integrator_output;
    float sogi_backward_integrator_output;
    float update_period;
    float freq_radians;
    float center_freq_radians;
    float freq_Hz;
    float fll_integrator;
} FLL_t;

/**
 * @brief initialize FLL_t struct.
 *
 * @param s pointer to FLL_t struct
 * @param k_gain_sogi gain of SOGI
 * @param gamma gamma value for SOGI-PLL
 * @param dt period of calculation
 * @param fc center frequency in Hz
 */
void init_fll(FLL_t *s, float k_gain_sogi, float gamma, float dt, float fc);

/**
 * @brief calculation of FLL.
 *
 * @param s pointer fo FLL_t struct
 * @param signal input signal
 * @return float instant calculated frequency
 */
float calc_fll(FLL_t *s, float signal);

#ifdef __cplusplus
}
#endif

#endif// INCLUDE_FLL_H_
