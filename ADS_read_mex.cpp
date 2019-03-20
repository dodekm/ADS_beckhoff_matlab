#include "mex.h"
#include "matrix.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#include "ADS_lib.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
   double *outMatrix; 
   double *inMatrix;
    plhs[0] = mxCreateDoubleScalar(0);
    outMatrix = mxGetPr(plhs[0]);
    inMatrix=mxGetPr(prhs[0]);
    
    AmsAddr   Addr;
	PAmsAddr  pAddr = &Addr;
	
	ADS_init(pAddr, 0, ADS_create_ip(10, 3, 1, 138, 3, 1), AMSPORT_R0_PLC_TC3);
	ADS_variable* var=(ADS_variable*)malloc(sizeof(ADS_variable));
	ADS_init_var_INT(var, "GVL.var");
    
    *(((ADS_INT16*)(var->data_pointer)))=(int)inMatrix[0];
    
    ADS_variable_write(pAddr, var);
    ADS_variable_read(pAddr, var);
    
    outMatrix[0]=(double)*(((ADS_INT16*)(var->data_pointer)));
    
    ADS_release_handler(pAddr, var);
	ADS_destroy_var(var);
    
}