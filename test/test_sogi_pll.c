#include "stdio.h"
#include "../include/pll_sogi.h"

int main(int argc, char const *argv[])
{
    pll_sogi_s PLL_s ;
    pll_sogi_s * p_PLL_s = & PLL_s ;
    double phase = 0 , sine_wave = 0 ;

    init_pll_sogi(p_PLL_s, 0.1, 1, 1e-4) ;

    FILE * fp = fopen("test_sogi_qsg.txt", "w") ;

    for(int i = 0 ;i < 1e4 ; i ++ ){
        sine_wave = sin(DOUBLE_PI_PLL_SOGI * 50 * i * 1e-4 + 1.57) ;
        phase = calc_pll_sogi(p_PLL_s, 311 *  sine_wave ) ;
        fprintf(fp, "%lf,%lf,%lf,%lf\r\n", sine_wave, phase, sin(phase), p_PLL_s->angle_freq ) ;
    }

    fclose(fp) ;

    return 0;
}
