#include "pll.h"
#include <math.h>

/******************Variables*******************/

double InitPhase = INIT_PHASE ;
double InitFreq = INIT_FREQ ;
double UgInitPhase = UG_INIT_PHASE;

//Maximum and Minimum Frequency:
double FreqMax = FREQ_MAX ;
double FreqMin = FREQ_MIN ;

//PID Para:
double KpPLL = 120;
double KiPLL = 2800 ;
double WtUpperLimit = 1.25 * 2 * PI * INIT_FREQ ;
double WtLowerLimit = 0.75 * 2 * PI * INIT_FREQ ;

double PI_IntgrationPLL = 2 * PI * INIT_FREQ ;
double PI_ProportionPLL = 0 ;
double PI_OutPLL = 0.0 ;


double SinWt = 0 ;
double CosWt = 1 ;

double W_PIOut = 0 ;
double Freq_PIOut = 0 ;

double Wt = 0;
double WtSum = 0 ;

double UgMax = 0.5f ;

// Integration Queue and the pointer
double QueueSum[SIZE_OF_QUEUE] = {0.0} ;
double * pQueueSum_NminusOne = QueueSum ;
double * pQueueSum_N = QueueSum + 1 ;

double * pQueueSum_UpperLimit = QueueSum + SIZE_OF_QUEUE -1 ;
double * pQueueSum_LowerLimit = QueueSum ;

// Delayed pointer
double * pQueueSum_Delayed ;

int NumDelayedBeats = 0 ;
double f_NumDelayedBeats = 0.0 ;
int CeilNumeDelayedBeats = 0 ;
int NumDelayedQueueSum = 0 ;

//long NumDelayedBeats = 0 ;
//double f_NumDelayedBeats = 0.0 ;
//long CeilNumeDelayedBeats = 0 ;
//long NumDelayedQueueSum = 0 ;

double Correction = 0 ;
double errorToCeil = 0;

double MeanValue_N = 0.0 ;
double MeanValue_NminusOne = 0.0 ;

// Grid Voltage
double UgridPLL = 0 ;

double UgridMulCosWt_N = 0 ;
double UgridMulCosWt_NminusOne = 0 ;

// 2nd-Order Filter Initialization
double W_NminusOne = 0 ;
double Freq_N = 0 ;
double Freq_M = 0 ;
double Freq = 0 ;

double Ad11 = A11 ;
double Ad12 = A12 ;
double Ad21 = A21 ;
double Ad22 = A22 ;

double Bd11 = B11 ;
double Bd21 = B21 ;

double Cd11 = C11 ;
double Cd12 = C12 ;

double Dd11 = D11 ;

double x0d11_N = X11 ;
double x0d21_N = X21 ;

double x0d11_NminusOne ;
double x0d21_NminusOne ;

void InitPLL(void)
{
	int i_pll = 0 ;
    // Phase of the Grid
	UgInitPhase = 0 ;

	// PLL Para
	FreqMax = FREQ_MAX ;
	FreqMin = FREQ_MIN ;
	InitPhase = INIT_PHASE;
	InitFreq = INIT_FREQ;
	KpPLL = KP_PLL;
	KiPLL = KI_PLL;

	// PLL Output initialization 
    Freq = InitFreq ;
    Wt = InitPhase ;
    SinWt = sin(Wt);
    CosWt = cos(Wt);

	// Mean value initialization
	MeanValue_NminusOne = 0;
	MeanValue_N = 0;
    // Initialize the QUeue
	for (i_pll = 0; i_pll < SIZE_OF_QUEUE; i_pll++)
	{
		QueueSum[i_pll] = 0.0 ;
	}
	UgridMulCosWt_NminusOne = 0;
	UgridMulCosWt_N = 0;

	// PI limit
	WtUpperLimit = 1.25 * 2 * PI * InitFreq;
	WtLowerLimit = 0.75 * 2 * PI * InitFreq;
	PI_IntgrationPLL = 2 * PI * InitFreq;

	// Freq initialization
	Freq_N = InitFreq;
	Freq_M = InitFreq;

	// W initialization
	W_NminusOne = 0; // InitFreq * DOUBLE_PI;
	WtSum = InitPhase;

	// 2-nd Order Filter-State space
    Ad11 = A11 ;
    Ad12 = A12 ;
    Ad21 = A21 ;
    Ad22 = A22 ;

    Bd11 = B11 ;
    Bd21 = B21 ;

    Cd11 = C11 ;
    Cd12 = C12 ;

    Dd11 = D11 ;

    x0d11_N = X11 ;
    x0d21_N = X21 ;

    x0d11_NminusOne = X11 ;
    x0d21_NminusOne = X21 ;


	pQueueSum_NminusOne = QueueSum;
	pQueueSum_N = pQueueSum_NminusOne + 1;

	pQueueSum_UpperLimit = QueueSum + ( SIZE_OF_QUEUE - 1 );
	pQueueSum_LowerLimit = QueueSum;
}

double UpdatePLL( double UgridSampled)
{
    UgMax = (UgMax > UgridSampled)?UgMax:UgridSampled ;

    UgMax = (UgMax > 320)? 320 : UgMax ; // Limit the maximum of UgMax ;

    UgridPLL = UgridSampled / UgMax ;
    UgridMulCosWt_N = UgridPLL * CosWt ;

    // Delayed Sum Calc
    *pQueueSum_N = *pQueueSum_NminusOne + HALF_TS * ( UgridMulCosWt_N + UgridMulCosWt_NminusOne);

    double f_temp = Freq ;

    if(f_temp > FreqMax )
    {
    	f_temp = FreqMax ;
    }
    else if (f_temp < FreqMin )
    {
    	f_temp = FreqMin ;
    }

    //NumDelayedBeats = (int)(1 / f_temp / TS) ;
    //f_NumDelayedBeats = 1 / f_temp / TS ;

	NumDelayedBeats = (int)(10000 / f_temp);
	f_NumDelayedBeats = 10000 / f_temp ;

    CeilNumeDelayedBeats = NumDelayedBeats + 1 ;

    NumDelayedQueueSum = CeilNumeDelayedBeats  ;

    errorToCeil = f_NumDelayedBeats - CeilNumeDelayedBeats ;
    Correction = errorToCeil / f_NumDelayedBeats * ( 0.5 * ( UgridMulCosWt_N - UgridMulCosWt_NminusOne) * errorToCeil + UgridMulCosWt_N );
	UgridMulCosWt_NminusOne = UgridMulCosWt_N;

    if(pQueueSum_N - pQueueSum_LowerLimit < NumDelayedQueueSum )
    {
        pQueueSum_Delayed = pQueueSum_N + (300 - NumDelayedQueueSum ) ;  
    }
    else 
    {
        pQueueSum_Delayed = pQueueSum_N - NumDelayedQueueSum ;
    }

	MeanValue_N = (*pQueueSum_N - *pQueueSum_Delayed) * Freq + Correction;

	// Pointer ++ after meanvalue calc completed
    pQueueSum_N ++ ;
    pQueueSum_NminusOne ++ ;

    if(pQueueSum_N > pQueueSum_UpperLimit)
    {
        pQueueSum_N = pQueueSum_LowerLimit ;
    }
    else if(pQueueSum_NminusOne > pQueueSum_UpperLimit)
    {
        pQueueSum_NminusOne = pQueueSum_LowerLimit ;
    }

    // PI Control
    PI_ProportionPLL = KpPLL * MeanValue_N ;
    PI_IntgrationPLL += KiPLL * MeanValue_NminusOne * TS  ; 
	MeanValue_NminusOne = MeanValue_N;

    if(PI_IntgrationPLL > WtUpperLimit)
    {
        PI_IntgrationPLL = WtUpperLimit ;
    }
    else if(PI_IntgrationPLL < WtLowerLimit )
    {
        PI_IntgrationPLL = WtLowerLimit ;
    }

    PI_OutPLL = PI_IntgrationPLL + PI_ProportionPLL ;

    if(PI_OutPLL > WtUpperLimit)
    {
        PI_OutPLL = WtUpperLimit ;
    }
    else if(PI_OutPLL < WtLowerLimit )
    {
        PI_OutPLL = WtLowerLimit ;
    }

    // The estimated angular speed is the output of PI;
    W_PIOut = PI_OutPLL ;

    Freq = Freq_N ;
    Freq_PIOut = W_PIOut / DOUBLE_PI ;
    if( Freq_PIOut > ( Freq_M + 12 ))
    {
        Freq_M += 12 ;
    }
    else if( Freq_PIOut < ( Freq_M - 12) )
    {
        Freq_M -= 12 ;
    }
    else
    {
    	Freq_M = Freq_PIOut ;
    }

    // Freq_N = Cd * x0d + Dd * Freq_NminusOne ;
    // x0d = Ad * x0d + Bd * Freq_NminusOne ;

    Freq_N = Cd11 * x0d11_NminusOne + Cd12 * x0d21_NminusOne  + Dd11 * Freq_M;

    x0d11_N = Ad11 * x0d11_NminusOne + Ad12 * x0d21_NminusOne + Bd11 * Freq_M ;
    x0d21_N = Ad21 * x0d11_NminusOne + Ad22 * x0d21_NminusOne + Bd21 * Freq_M;

	x0d11_NminusOne = x0d11_N;
	x0d21_NminusOne = x0d21_N;



    WtSum += TS * W_NminusOne ;
	W_NminusOne = W_PIOut;


	if (WtSum > DOUBLE_PI)
	{
		WtSum -= DOUBLE_PI;
		
	}
	Wt = WtSum;
	

    SinWt = sin(Wt);
    CosWt = cos(Wt);

    return Freq ;
}
