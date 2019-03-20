#include "ADS_lib.h"


void ADS_stop_plc(PAmsAddr  pAddr)
{
	USHORT device_state = ADSSTATE_STOP;
	AdsSyncWriteControlReq(pAddr, device_state, 0, 0, NULL);

}

void ADS_start_plc(PAmsAddr  pAddr)
{
	USHORT device_state = ADSSTATE_RUN;
	AdsSyncWriteControlReq(pAddr, device_state, 0, 0, NULL);

}


void ADS_init_var_INT(ADS_variable* var, const char* variable_name)
{
	var->lHdlVar = 0;
	var->data_type_size = sizeof(ADS_INT16);
	var->data_pointer = malloc(var->data_type_size);
	strcpy_s(var->name, variable_name);
}

void ADS_destroy_var(ADS_variable* var)
{
	free(var->data_pointer);
	free(var);
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

