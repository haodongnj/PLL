#include <math.h>
#include <pll_sogi.h>
#include <stdio.h>

/// in case of compiling under MS windows
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const double ts = 5e-5;
static const double f1 = 49.5;
static const double f2 = 50.5;
static const double amplitude = 311.0;

int main() {
    PLL_SOGI_t s;
    double phase = 0, sine_wave = 0;
    double theta = 0;

    init_pll_sogi(&s, 2.0, 0.2, 1.0, ts, 50);

    FILE *fp = fopen("result.txt", "w");

    for (int i = 0; i < 1e4; i++) {
        theta += 2 * M_PI * f1 * ts;
        sine_wave = sin(theta);
        phase = calc_pll_sogi(&s, amplitude * sine_wave);
        fprintf(fp, "%lf,%lf,%lf,%lf,%lf\r\n",
                sine_wave,
                phase,
                sin(phase),
                s.angle_freq,
                i * ts);
    }

    // change frequency to f2 here
    for (int i = 1e4; i < 2e4; i++) {
        theta += 2 * M_PI * f2 * ts;
        sine_wave = sin(theta);
        phase = calc_pll_sogi(&s, amplitude * sine_wave);
        fprintf(fp, "%lf,%lf,%lf,%lf,%lf\r\n",
                sine_wave,
                phase,
                sin(phase),
                s.angle_freq,
                i * ts);
    }

    fclose(fp);

    return 0;
}
