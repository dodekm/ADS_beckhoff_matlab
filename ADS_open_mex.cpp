#include "mex.h"
#include "matrix.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#include "ADS_lib.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    
    if(nlhs!=0||nrhs!=0)
    {
        mexErrMsgTxt("zly_pocet_vstupnych/vystupnych_argumentov");
        return;
    }
    
    
    ADS_open();
    
    
}