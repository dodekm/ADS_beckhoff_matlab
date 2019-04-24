/* Copyright 2003-2014 The MathWorks, Inc. */

#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME  ADS_read_SFUN

// Need to include simstruc.h for the definition of the SimStruct and
// its associated macro definitions.
#include "simstruc.h"

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

#include "ADS_lib.h"


#define N_PARAMS 3

#define IP_ADRESS_IDX 0
#define IP_ADRESS_PARAM(S) ssGetSFcnParam(S,IP_ADRESS_IDX)

#define VAR_NAME_IDX  1
#define VAR_NAME_PARAM(S) ssGetSFcnParam(S,VAR_NAME_IDX)


#define VAR_TYPE_IDX  2
#define VAR_TYPE_PARAM(S) ssGetSFcnParam(S,VAR_TYPE_IDX)


// Function: mdlInitializeSizes ===============================================
// Abstract:
//    The sizes information is used by Simulink to determine the S-function
//    block's characteristics (number of inputs, outputs, states, etc.).
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, N_PARAMS);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }
    
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    
    if (!ssSetNumInputPorts(S, 0)) return;
    
    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 1);
    
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 2);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    
    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);
    ssSetOptions(S, 0);
    
}


// Function: mdlInitializeSampleTimes =========================================
// Abstract:
//   This function is used to specify the sample time(s) for your
//   S-function. You must register the same number of sample times as
//   specified in ssSetNumSampleTimes.
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
}

#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)

static void mdlStart(SimStruct *S)
{
    
    PAmsAddr  pAddr = (AmsAddr*) new AmsAddr;
    ADS_variable* var = (ADS_variable*) new ADS_variable;
    
    ssSetPWorkValue(S, 0, (void *)pAddr);
    ssSetPWorkValue(S, 1, (void *)var);
    
    const mxArray* mx_ipadress=IP_ADRESS_PARAM(S);
    const mxArray* mx_var_name=VAR_NAME_PARAM(S);
    const mxArray* mx_var_type=VAR_TYPE_PARAM(S);
    
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
        return;
    }
    
    if(!mxIsChar(mx_var_name))
    {
        return;
        
    }
    char* var_name= mxArrayToString(mx_var_name);
    
    if (!mxIsScalar(mx_var_type))
    {
        return;
    }
    
    TC_type type = (TC_type)mxGetScalar(mx_var_type);
    ADS_init(pAddr, 0, ADS_create_ip(netid[0], netid[1], netid[2],netid[3], netid[4], netid[5]), AMSPORT_R0_PLC_TC3);
    ADS_init_var(var, var_name,type);
    
    
    
}
#endif


// Function: mdlOutputs =======================================================
// Abstract:
//   In this function, you compute the outputs of your S-function
//   block.
static void mdlOutputs(SimStruct *S,int_T tid)
{
    PAmsAddr  pAddr = (PAmsAddr) ssGetPWorkValue(S, 0);
    ADS_variable* var =(ADS_variable*) ssGetPWorkValue(S, 1);
    
    // Get data addresses of I/O
    InputRealPtrsType  u = ssGetInputPortRealSignalPtrs(S,0);
    real_T *y = ssGetOutputPortRealSignal(S, 0);
    ADS_variable_read(pAddr, var);
    *y=ADS_var_value_get_double(var);
    
}

/* Function: mdlUpdate ======================================================
 * Abstract:
 *    This function is called once for every major integration time step.
 *    Discrete states are typically updated here, but this function is useful
 *    for performing any tasks that should only take place once per
 *    integration step.
 */

#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
static void mdlUpdate(SimStruct *S, int_T tid)
{
    
}
#endif
/* Function: mdlDerivatives =================================================
 * Abstract:
 *    In this function, you compute the S-function block's derivatives.
 *    The derivatives are placed in the derivative vector, ssGetdX(S).
 */

#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)

static void mdlDerivatives(SimStruct *S)
{
    
}
#endif

// Function: mdlTerminate =====================================================
// Abstract:
//   In this function, you should perform any actions that are necessary
//   at the termination of a simulation.  For example, if memory was
//   allocated in mdlStart, this is the place to free it.
static void mdlTerminate(SimStruct *S)
{
    PAmsAddr  pAddr = (PAmsAddr) ssGetPWorkValue(S, 0);
    ADS_variable* var =(ADS_variable*) ssGetPWorkValue(S, 1);
    ADS_release_handler(pAddr, var);
    
    delete pAddr;
    delete var;
}

// Required S-function trailer
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
