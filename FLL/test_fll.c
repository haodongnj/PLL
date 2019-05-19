#include "stdio.h"
#include "fll.h"
#include "math.h"

int main(int argc, char const *argv[])
{
    fll_s FLL_s ;
    fll_s * p_FLL_s = & FLL_s ;
    float freq = 0, sine_wave = 0, t ;

    init_fll(p_FLL_s, 1.414213562, 0.5, 5e-5) ;

    FILE * fp = fopen("test_fll.txt", "w") ;

    for(int i = 0 ;i < 2e5 ; i ++ ){
        t = (i+1) * 5e-5 ;   
        sine_wave = sinf(DOUBLE_PI_FLL * 50 * t ) ;
        freq = calc_fll(p_FLL_s, 311 *  sine_wave ) ;
        fprintf(fp, "%f,%f\r\n", t, freq ) ;
    }

    fclose(fp) ;

    return 0;
}
