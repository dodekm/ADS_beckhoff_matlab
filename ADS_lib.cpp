#include "ADS_lib.h"


unsigned long TC_type_size(TC_type data_type)
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

long ADS_open()
{
    long	nPort;
    nPort = AdsPortOpen();
    return nPort;
}


long ADS_close()
{
    return AdsPortClose();
}

long ADS_init(PAmsAddr pAddr, bool use_local, AmsNetId ipadress, unsigned short port)
{
    long    nErr;
    if (use_local==true)
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
    var->data_type_size = TC_type_size(data_type);
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
    
    if (var->lHdlVar == 0 && !var->name.empty())
    {
        nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(var->lHdlVar), &(var->lHdlVar), var->name.length(), (void*)var->name.c_str());
        if (nErr)
            return nErr;
    }
	if (var->lHdlVar != 0)
    nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, var->lHdlVar, var->data_type_size, var->data_pointer);
    if (nErr)
        return nErr;
    return 0;
}

long ADS_variable_write(PAmsAddr  pAddr, ADS_variable* var)
{
    long    nErr;
    
    if (var->lHdlVar == 0 && !var->name.empty())
    {
        nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(var->lHdlVar), &(var->lHdlVar), var->name.length(), (void*)var->name.c_str());
        if (nErr)
            return nErr;
    }
	if(var->lHdlVar!=0)
    nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, var->lHdlVar, var->data_type_size, var->data_pointer);
    if (nErr)
        return nErr;
    return 0;
}


double ADS_variable_read_by_name(PAmsAddr  pAddr, ADS_variable* var)
{
	long    nErr;

	if (var->lHdlVar == 0 && !var->name.empty())
	{
		nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_VALBYNAME, 0x0, var->data_type_size, var->data_pointer, var->name.length(), (void*)var->name.c_str());
		if (nErr)
			return ADS_var_value_get_double(var);
	}
	return 0;
}


long ADS_release_handler(PAmsAddr  pAddr, ADS_variable* var)
{
    
    long    nErr;
	if(var->lHdlVar != 0)
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

AdsSymbolUploadInfo ADS_all_num_and_size(PAmsAddr pAddr)
{
	long nErr;
	AdsSymbolUploadInfo symbolInfo;
	nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_UPLOADINFO, 0, sizeof(symbolInfo), &symbolInfo);
	return symbolInfo;
}
PAdsSymbolEntry ADS_alloc_space_for_AdsSymbolEntry(AdsSymbolUploadInfo symbolInfo)
{
	return (PAdsSymbolEntry) new char[symbolInfo.nSymSize];
}


PAdsSymbolEntry ADS_all_var_info_read(PAmsAddr pLocalAdress, AdsSymbolUploadInfo symbolInfo)
{
	long nErr;
	PAdsSymbolEntry pSymbolEntry=ADS_alloc_space_for_AdsSymbolEntry(symbolInfo);
	nErr = AdsSyncReadReq(pLocalAdress, ADSIGRP_SYM_UPLOAD, 0, symbolInfo.nSymSize, pSymbolEntry);
	return pSymbolEntry;
}


TC_type ADS_get_TC_type_from_symbol_entry(PAdsSymbolEntry symbol_entry)
{
	return (TC_type) symbol_entry->dataType;
}

ADS_variable ADS_construct_variable(PAdsSymbolEntry symbol_entry)
{
	ADS_variable  symbol;
	symbol.symbol_entry = *symbol_entry;
	std::string symbol_name = std::string((PADSSYMBOLNAME(symbol_entry)));
	std::string symbol_type = std::string((PADSSYMBOLTYPE(symbol_entry)));

	TC_type type = ADS_get_TC_type_from_symbol_entry(symbol_entry);

	ADS_init_var(&symbol, symbol_name, type);
	return symbol;
}



std::vector<ADS_variable>ADS_get_variables(AdsSymbolUploadInfo symbolInfo, PAdsSymbolEntry symbol_entry)
{
	std::vector<ADS_variable> variables;
	for (int i = 0; i < (symbolInfo.nSymbols); i++)
	{
		
		ADS_variable  symbol = ADS_construct_variable(symbol_entry);
		variables.push_back(symbol);
		symbol_entry = PADSNEXTSYMBOLENTRY(symbol_entry);
	}
	if(symbol_entry!=NULL)
	free (symbol_entry);
	return variables;

}
