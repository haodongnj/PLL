#include <math.h>
#include <pll_sogi.h>
#include <stdio.h>

int main() {
  PLL_SOGI_t s;
  double phase = 0, sine_wave = 0;

  init_pll_sogi(&s, 0.1, 1, 1e-4, 50);

  FILE *fp = fopen("result.txt", "w");

  for (int i = 0; i < 5e3; i++) {
    sine_wave = sin(2 * M_PI * 50 * i * 1e-4 + 1.57);
    phase = calc_pll_sogi(&s, 311 * sine_wave);
    fprintf(fp, "%lf,%lf,%lf,%lf,%lf\r\n", 
        sine_wave, 
        phase, 
        sin(phase),
        s.angle_freq,
        i * 1e-4);
  }

  fclose(fp);

  return 0;
}
