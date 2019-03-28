#include "ADS_lib.h"


unsigned long type_size(TC_type data_type)
{
	switch (data_type)
	{
		case TC_BOOL_type:
			return sizeof(TC_BOOL);
		case TC_BYTE_type:
			return sizeof(TC_BYTE);
		case TC_WORD_type:
			return sizeof(TC_WORD);
		case TC_DWORD_type:
			return sizeof(TC_DWORD);
		case TC_INT_type:
			return sizeof(TC_INT);
		case TC_DINT_type:
			return sizeof(TC_DINT);
		case TC_LINT_type:
			return sizeof(TC_LINT);
		case TC_USINT_type:
			return sizeof(TC_USINT);
		case TC_UINT_type:
			return sizeof(TC_UINT);
		case TC_UDINT_type:
			return sizeof(TC_UDINT);
		case TC_ULINT_type:
			return sizeof(TC_ULINT);
		case TC_REAL_type:
			return sizeof(TC_REAL);
		case TC_LREAL_type:
			return sizeof(TC_LREAL);
		default:
			return 0;
	}

}

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


void ADS_init_var(ADS_variable* var, const std::string variable_name, TC_type data_type)
{
	var->lHdlVar = 0;
	var->data_type_size = type_size(data_type);
	var->data_type = data_type;
	var->data_pointer = &var->TC_LINT_data;
	var->TC_LINT_data = 0;
	var->name = variable_name;

}

void ADS_destroy_var(ADS_variable* var)
{
	delete var;
}


long ADS_variable_read(PAmsAddr  pAddr, ADS_variable* var)
{
	long    nErr;

	if (var->lHdlVar == 0)
	{
		nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(var->lHdlVar), &(var->lHdlVar), var->name.length(), (void*)var->name.c_str());
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
		nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(var->lHdlVar), &(var->lHdlVar), var->name.length(), (void*)var->name.c_str());
		if (nErr)
			return nErr;
	}
	nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, var->lHdlVar, var->data_type_size, var->data_pointer);
	if (nErr)
		return nErr;
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
	var->lHdlVar = 0;
	return nErr;
}




double ADS_var_value_get_double(ADS_variable* var)
{

	switch (var->data_type)
	{
	case		TC_BOOL_type:
		return (double)var->TC_BOOL_data;
		break;
	case		TC_BYTE_type:
		return (double)var->TC_BYTE_data;
		break;
	case		TC_WORD_type:
		return (double)var->TC_WORD_data;
		break;
	case		TC_DWORD_type:
		return (double)var->TC_DWORD_data;
		break;
	case		TC_INT_type:
		return (double)var->TC_INT_data;
		break;
	case		TC_DINT_type:
		return (double)var->TC_DINT_data;
		break;
	case		TC_LINT_type:
		return (double)var->TC_LINT_data;
		break;
	case		TC_USINT_type:
		return (double)var->TC_USINT_Data;
		break;
	case		TC_UINT_type:
		return (double)var->TC_UINT_data;
		break;
	case		TC_UDINT_type:
		return (double)var->TC_UINT_data;
		break;
	case		TC_ULINT_type:
		return (double)var->TC_ULINT_data;
		break;
	case		TC_REAL_type:
		return (double)var->TC_REAL_data;
		break;
	case		TC_LREAL_type:
		return (double)var->TC_LREAL_data;
		break;
	
	}
	return 0;

}

void ADS_var_value_set_double(ADS_variable* var, double val)
{
	switch (var->data_type)
	{
	case		TC_BOOL_type:
		var->TC_BOOL_data=val;
		break;
	case		TC_BYTE_type:
		var->TC_BYTE_data=val;
		break;
	case		TC_WORD_type:
		var->TC_WORD_data=val;
		break;
	case		TC_DWORD_type:
		var->TC_DWORD_data=val;
		break;
	case		TC_INT_type:
		var->TC_INT_data=val;
		break;
	case		TC_DINT_type:
		var->TC_DINT_data=val;
		break;
	case		TC_LINT_type:
		var->TC_LINT_data=val;
		break;
	case		TC_USINT_type:
		var->TC_USINT_Data=val;
		break;
	case		TC_UINT_type:
		var->TC_UINT_data=val;
		break;
	case		TC_UDINT_type:
		var->TC_UINT_data=val;
		break;
	case		TC_ULINT_type:
		var->TC_ULINT_data=val;
		break;
	case		TC_REAL_type:
		var->TC_REAL_data=val;
		break;
	case		TC_LREAL_type:
		var->TC_LREAL_data=val;
		break;

	}
}

