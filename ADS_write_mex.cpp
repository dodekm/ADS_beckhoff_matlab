#include "mex.h"
#include "matrix.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#include "ADS_lib.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    if(nlhs==0&&nrhs==1)
    {
   double *inMatrix;
    inMatrix = mxGetPr(prhs[0]);
    
    AmsAddr   Addr;
	PAmsAddr  pAddr = &Addr;
	
	ADS_init(pAddr, 0, ADS_create_ip(10, 3, 1, 138, 3, 1), AMSPORT_R0_PLC_TC3);
    ADS_variable var;
	ADS_init_var_INT(&var, "GVL.vat",TC_INT_type);
   
    
    var.TC_INT_data=inMatrix[0];
    ADS_variable_write(pAddr, &var);
   
    ADS_release_handler(pAddr, &var);
    ADS_deinit();
    
    }
}