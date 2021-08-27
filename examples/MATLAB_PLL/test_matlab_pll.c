#include <stdio.h>
#include <pll_sogi.h>
#include <math.h>

extern double Freq;
extern double errorToCeil;
extern double MeanValue_N;
extern double W_PIOut;
extern double * pQueueSum_NminusOne;
extern double UgInitPhase;

int main()
{
	double UgSampled = 0 ;

	FILE * fp;
	fp = fopen("C:\\Users\\donghao\\Desktop\\PLL\\C\\PLL_DH\\PLLResults.txt", "w+");
	//fprintf(fp, "Data\n");
	if (fp == NULL)
	{
		exit(0);
	}

	InitPLL();
	int i = 0;
	for( i = 0 ; i < 10000 ; i ++ )
	{
		UgSampled = sin( 314 * 1e-4 * i + UgInitPhase);
		UpdatePLL(UgSampled);
		//printf("Frequency: %lf \n", UpdatePLL(UgSampled)) ;
		fprintf(fp, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", TS * i, Freq,errorToCeil, MeanValue_N, W_PIOut, *pQueueSum_NminusOne);

	}
	fclose(fp);
	return 0 ;
}
