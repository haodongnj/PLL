#include <stdio.h>
#include <fll.h>
#include <math.h>

/// in case of compiling under MS windows
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(int argc, char const *argv[])
{
    FLL_t s ;
    float freq = 0, sine_wave = 0, t ;

    init_fll(&s, 1.414213562, 0.5, 5e-5, 50) ;

    FILE * fp = fopen("result.txt", "w") ;

    for(int i = 0 ;i < 2e3 ; i ++ ){
        t = (i+1) * 5e-5 ;
        sine_wave = sin(2 * M_PI * 50 * t ) ;
        freq = calc_fll(&s, 311 *  sine_wave ) ;
        fprintf(fp, "%f,%f\r\n", t, freq ) ;
    }

    fclose(fp) ;

    return 0;
}
