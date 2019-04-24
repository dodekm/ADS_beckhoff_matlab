#include "mex.h"
#include "matrix.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#include "ADS_lib.h"

void mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
   if(nlhs!=0||nrhs!=1)
    {
    mexErrMsgTxt("zly_pocet_vstupnych/vystupnych_argumentov");
    return;
    }
    
   const mxArray* mx_ipadress=prhs[0];

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
   
     
    AmsAddr   Addr;
	PAmsAddr  pAddr = &Addr;
	ADS_init(pAddr, 0, ADS_create_ip(netid[0], netid[1], netid[2],netid[3], netid[4], netid[5]), AMSPORT_R0_PLC_TC3);
   
    AdsSymbolUploadInfo symbols_info= ADS_all_num_and_size(pAddr);
    PAdsSymbolEntry symbols_entry=ADS_all_var_info_read(pAddr, symbols_info);

    std::vector<ADS_variable> ADS_variables = ADS_get_variables(symbols_info, symbols_entry);
   
    for(std::vector<ADS_variable>::iterator it=ADS_variables.begin();it!=ADS_variables.end();it++)
    {
        ADS_variable var=*it;
        mexPrintf("%s \n",var.name.c_str());
    }
   
    
}