#include "mex.h"
#include "matrix.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#include "ADS_lib.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    
    
    if(nlhs==1&&nrhs==2)
    {
      const mwSize *dims;
      dims = mxGetDimensions(prhs[0]);
      int rows = (int)dims[0]; 
      int cols = (int)dims[1];
      
      double* netid;
      if(cols==6) 
      {
        netid=(double*)mxGetPr(prhs[0]);
      }
      else return;
     
      
       if(!mxIsChar(prhs[1]))
           return;
     
      char* var_name= mxArrayToString(prhs[1]);
      
      
    //10, 3, 1, 138, 3, 1
    AmsAddr   Addr;
	PAmsAddr  pAddr = &Addr;
	ADS_init(pAddr, 0, ADS_create_ip(netid[0], netid[1], netid[2],netid[3], netid[4], netid[5]), AMSPORT_R0_PLC_TC3);
    ADS_variable var;
	
    ADS_init_var_INT(&var, var_name,TC_INT_type);
    ADS_variable_read(pAddr, &var);
    
    
    double *outMatrix; 
    plhs[0] = mxCreateDoubleScalar(0);
    outMatrix = mxGetPr(plhs[0]);
    outMatrix[0]=(double)var.TC_INT_data;
    
    ADS_release_handler(pAddr, &var);
    ADS_deinit();
    
    
    }
}