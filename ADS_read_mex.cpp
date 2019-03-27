#include "mex.h"
#include "matrix.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#include "ADS_lib.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
   
    if(nlhs!=1||nrhs!=2)
    {
    mexErrMsgTxt("zly_pocet_vstupnych/vystupnych_argumentov");
    return;
    }
    
   const mxArray* mx_ipadress=prhs[0];
   const mxArray* mx_var_name=prhs[1];
   mxArray* mx_var_value;
    
      const mwSize *dims;
      dims = mxGetDimensions(mx_ipadress);
      int rows = (int)dims[0]; 
      int cols = (int)dims[1];
      
      double* netid;
      if(cols==6&&rows==1) 
      {
        netid=mxGetPr(mx_ipadress);
      }
      else 
      {
          mexErrMsgTxt("zly_format_IP");
          return;
      }
   
       if(!mxIsChar(prhs[1]))
       {
           mexErrMsgTxt("zly_format_nazvu_premennej");
           return;
           
       }
      char* var_name= mxArrayToString(mx_var_name);
      
    AmsAddr   Addr;
	PAmsAddr  pAddr = &Addr;
	if(ADS_init(pAddr, 0, ADS_create_ip(netid[0], netid[1], netid[2],netid[3], netid[4], netid[5]), AMSPORT_R0_PLC_TC3))
    {
        mexErrMsgTxt("ADS_connect_error");
        return;
    }
    ADS_variable var;
    ADS_init_var_INT(&var, var_name,TC_INT_type);
   
   if(ADS_variable_read(pAddr, &var))
   {
        mexErrMsgTxt("ADS_read_error");
        ADS_deinit();
        return;
   }
    double *outMatrix; 
    mx_var_value = mxCreateDoubleScalar(0);
    outMatrix = mxGetPr(mx_var_value);
    outMatrix[0]=(double)var.TC_INT_data;
   
    plhs[0]= mx_var_value;
    ADS_release_handler(pAddr, &var);
    
}