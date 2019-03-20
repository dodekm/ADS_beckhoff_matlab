/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 * Copyright 1990-2013 The MathWorks, Inc.
 */
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

#include "TcAdsDef.h"
#include "TcAdsApi.h"

/*
 * You must specify the S_FUNCTION_NAME as the name of your S-function
 * (i.e. replace sfuntmpl_basic with the name of your S-function).
 */

#define S_FUNCTION_NAME  ADS_read_SFUN
#define S_FUNCTION_LEVEL 2

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

typedef struct
{
	unsigned long			lHdlVar;
	char					name[20];
	void*					data_pointer;
	unsigned long			data_type_size;
}ADS_variable;


AmsNetId ADS_create_ip(unsigned char ip_1, unsigned char ip_2, unsigned char ip_3, unsigned char ip_4, unsigned char ip_5, unsigned char ip_6);
long ADS_init(PAmsAddr pAddr, int use_local, AmsNetId ipadress, unsigned short port);
long ADS_variable_write_by_name(PAmsAddr  pAddr, const char* variable_name, void* source_pointer, unsigned int type_size);
long ADS_variable_read_by_name(PAmsAddr  pAddr, const char* variable_name, void* target_pointer, unsigned int type_size);
long ADS_variable_write(PAmsAddr  pAddr, ADS_variable* var);
long ADS_variable_read(PAmsAddr  pAddr, ADS_variable* var);

long ADS_variable_read_sumup(PAmsAddr  pAddr, const char* variable_name, void* target_pointer, unsigned int type_size);
long ADS_variable_write_sumup(PAmsAddr  pAddr, const char* variable_name, void* target_pointer, unsigned int type_size);
void ADS_print_error(long  nErr);
long ADS_release_handler(PAmsAddr  pAddr, ADS_variable* var);
long ADS_deinit();

void ADS_init_var_INT(ADS_variable* var, const char* variable_name)
{
	var->lHdlVar = 0;
	var->data_type_size = sizeof(ADS_INT16);
	var->data_pointer = malloc(var->data_type_size);
	strcpy(var->name,variable_name);
}

void ADS_destroy_var(ADS_variable* var)
{
	free(var->data_pointer);
	free(var);
}

void ADS_stop_plc(PAmsAddr  pAddr)
{
	USHORT device_state= ADSSTATE_STOP;
	AdsSyncWriteControlReq(pAddr, device_state,0 , 0,NULL);

}

void ADS_start_plc(PAmsAddr  pAddr)
{
	USHORT device_state = ADSSTATE_RUN;
	AdsSyncWriteControlReq(pAddr, device_state, 0, 0, NULL);

}

AmsAddr   Addr;
PAmsAddr  pAddr = &Addr;
ADS_variable* var;	


/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 */

/*====================*
 * S-function methods *
 *====================*/

/* Function: mdlInitializeSizes ===============================================
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
     * Set direct feedthrough flag (1=yes, 0=no).
     * A port has direct feedthrough if the input is used in either
     * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
     */
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 1);

    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);

}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
      
  
	ADS_init(pAddr, 0, ADS_create_ip(10, 3, 1, 138, 3, 1), AMSPORT_R0_PLC_TC3);
    var=(ADS_variable*)malloc(sizeof(ADS_variable));
	ADS_init_var_INT(var, "GVL.ventilator");
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



//#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
  }
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const real_T *u = (const real_T*) ssGetInputPortSignal(S,0);
    real_T       *y = ssGetOutputPortSignal(S,0);
    y[0] = u[0];
}



//#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
  }
#endif /* MDL_UPDATE */



//#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
    ADS_destroy_var(var);
}



AmsNetId ADS_create_ip(unsigned char ip_1, unsigned char ip_2, unsigned char ip_3, unsigned char ip_4, unsigned char ip_5, unsigned char ip_6)
{
	AmsNetId ip;
	ip.b[0] = ip_1;
	ip.b[1] = ip_2;
	ip.b[2] = ip_3;
	ip.b[3] = ip_4;
	ip.b[4] = ip_5;
	ip.b[5] = ip_6;
	return ip;
}

long ADS_init(PAmsAddr pAddr, int use_local, AmsNetId ipadress, unsigned short port)
{
	long    nErr;
	long	nPort;
	nPort = AdsPortOpen();

	if (use_local)
	{
		nErr = AdsGetLocalAddress(pAddr);
		return nErr;
	}

	else
	{
		pAddr->netId = ipadress;
	}
	pAddr->port = port;

	return 0;
}

long ADS_variable_write_by_name(PAmsAddr  pAddr, const char* variable_name, void* source_pointer, unsigned int type_size)
{

	long    nErr;
	ULONG     lHdlVar;
	int name_length;
	name_length = strlen(variable_name);

	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, name_length, (void*)variable_name);
	if (nErr)
		return nErr;
	nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, type_size, source_pointer);
	if (nErr)
		return nErr;
	return 0;
}

long ADS_variable_read_by_name(PAmsAddr  pAddr, const char* variable_name, void* target_pointer, unsigned int type_size)
{
	long    nErr;
	ULONG     lHdlVar;
	int name_length;
	name_length = strlen(variable_name);

	nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &lHdlVar, name_length, (void*)variable_name);
	if (nErr)
		return nErr;
	nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, type_size, target_pointer);
	if (nErr)
		return nErr;
	return 0;
}


long ADS_variable_read(PAmsAddr  pAddr, ADS_variable* var)
{
	long    nErr;

	if (var->lHdlVar == 0)
	{
		nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(var->lHdlVar), &(var->lHdlVar), strlen(var->name), (void*)var->name);
		if (nErr)
			return nErr;
	}
	nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, var->lHdlVar, var->data_type_size, var->data_pointer);
	if (nErr)
		return nErr;
	return 0;
}

long ADS_variable_write(PAmsAddr  pAddr, ADS_variable* var)
{
	long    nErr;

	if (var->lHdlVar == 0)
	{
		nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(var->lHdlVar), &(var->lHdlVar), strlen(var->name), (void*)var->name);
		if (nErr)
			return nErr;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, var->lHdlVar, var->data_type_size, var->data_pointer);
	if (nErr)
		return nErr;
	return 0;
}


long ADS_variable_read_sumup(PAmsAddr  pAddr, const char* variable_name, void* target_pointer, unsigned int type_size)
{
	long    nErr;
	return 0;
}

long ADS_variable_write_sumup(PAmsAddr  pAddr, const char* variable_name, void* target_pointer, unsigned int type_size)
{
	return 0;
}

long ADS_deinit()
{
	return AdsPortClose();
}

long ADS_release_handler(PAmsAddr  pAddr, ADS_variable* var)
{

	long    nErr;
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(var->lHdlVar), &(var->lHdlVar));
	return nErr;
}


void ADS_print_error(long   nErr)
{



}





/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif







