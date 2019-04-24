#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <map>
#include <string>

#include "TcAdsDef.h"
#include "TcAdsApi.h"


typedef bool			TC_BOOL;
typedef byte			TC_BYTE;
typedef unsigned short	TC_WORD;
typedef unsigned int	TC_DWORD;
typedef	short			TC_INT;
typedef int				TC_DINT;
typedef long			TC_LINT;
typedef byte			TC_USINT;
typedef	unsigned short	TC_UINT;
typedef unsigned int	TC_UDINT;
typedef unsigned long	TC_ULINT;
typedef float			TC_REAL;
typedef double			TC_LREAL;


enum TC_type {
    
    TC_BOOL_type,
    TC_BYTE_type,
    TC_WORD_type,
    TC_DWORD_type,
    TC_INT_type,
    TC_DINT_type,
    TC_LINT_type,
    TC_USINT_type,
    TC_UINT_type,
    TC_UDINT_type,
    TC_ULINT_type,
    TC_REAL_type,
    TC_LREAL_type
};

typedef struct
{
    unsigned long			lHdlVar;
    std::string				name;
    void*					data_pointer;
    TC_type					data_type;
    unsigned long			data_type_size;
    
	AdsSymbolEntry symbol_entry;

    union
    {
        TC_BOOL TC_BOOL_data;
        TC_BYTE TC_BYTE_data;
        TC_WORD TC_WORD_data;
        TC_DWORD TC_DWORD_data;
        TC_INT TC_INT_data;
        TC_DINT TC_DINT_data;
        TC_LINT TC_LINT_data;
        TC_USINT TC_USINT_Data;
        TC_UINT	TC_UINT_data;
        TC_UDINT TC_UDINT_data;
        TC_ULINT TC_ULINT_data;
        TC_REAL TC_REAL_data;
        TC_LREAL TC_LREAL_data;
    };
    
}ADS_variable;



unsigned long TC_type_size(TC_type data_type);
AmsNetId ADS_create_ip(unsigned char ip_1, unsigned char ip_2, unsigned char ip_3, unsigned char ip_4, unsigned char ip_5, unsigned char ip_6);

long ADS_open();
long ADS_close();
long ADS_init(PAmsAddr pAddr, bool use_local, AmsNetId ipadress, unsigned short port);

long ADS_variable_write(PAmsAddr  pAddr, ADS_variable* var);
long ADS_variable_read(PAmsAddr  pAddr, ADS_variable* var);
double ADS_variable_read_by_name(PAmsAddr  pAddr, ADS_variable* var);

void ADS_init_var(ADS_variable* var, const std::string variable_name, TC_type data_type);
long ADS_release_handler(PAmsAddr  pAddr, ADS_variable* var);

double ADS_var_value_get_double(ADS_variable* var);
void ADS_var_value_set_double(ADS_variable* var, double val);

void ADS_stop_plc(PAmsAddr  pAddr);
void ADS_start_plc(PAmsAddr  pAddr);

void ADS_destroy_var(ADS_variable* var);

AdsSymbolUploadInfo ADS_all_num_and_size(PAmsAddr pAddr);
PAdsSymbolEntry ADS_all_var_info_read(PAmsAddr pLocalAdress, AdsSymbolUploadInfo symbolInfo);

TC_type ADS_get_TC_type_from_symbol_entry(PAdsSymbolEntry symbol_entry);
ADS_variable ADS_construct_variable(PAdsSymbolEntry symbol_entry);

std::vector<ADS_variable>ADS_get_variables(AdsSymbolUploadInfo symbolInfo, PAdsSymbolEntry symbol_entry);

/*
template <typename	type>
        class ADS_template_variable
{
        private:
            unsigned long		lHdlVar;
            std::string			name;
            
            
        public:
            
            type	data;
            
            ADS_template_variable();
            ADS_template_variable(const std::string variable_name);
            
            long ADS_variable_write(PAmsAddr  pAddr);
            long ADS_variable_read(PAmsAddr  pAddr);
            long ADS_release_handler(PAmsAddr  pAddr);
            void set_double(double);
            double get_double(void);
            
};


template <typename	type>
        ADS_template_variable<type>::ADS_template_variable()
{
    lHdlVar = 0;
    data = 0;
    name = "";
    
}


template <typename	type>
        ADS_template_variable<type>::ADS_template_variable(const std::string variable_name)
{
    name = variable_name;
    lHdlVar = 0;
    data = 0;
}

template <typename	type>
        void ADS_template_variable<type>::set_double(double val)
{
    data = (type)val;
}

template <typename	type>
        double ADS_template_variable<type>::get_double(void)
{
    
    return (double)data;
}

template <typename	type>
        long ADS_template_variable<type>::ADS_variable_write(PAmsAddr  pAddr)
{
    long    nErr;
    
    if (lHdlVar == 0)
    {
        nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &(lHdlVar), name.length(), (void*)name.c_str());
        if (nErr)
            return nErr;
    }
    nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(type), (void*)&data);
    if (nErr)
        return nErr;
    return 0;
}

template <typename	type>
        long ADS_template_variable<type>::ADS_variable_read(PAmsAddr  pAddr)
{
    long    nErr;
    
    if (lHdlVar == 0)
    {
        nErr = AdsSyncReadWriteReq(pAddr, ADSIGRP_SYM_HNDBYNAME, 0x0, sizeof(lHdlVar), &(lHdlVar), name.length(), (void*)name.c_str());
        if (nErr)
            return nErr;
    }
    nErr = AdsSyncReadReq(pAddr, ADSIGRP_SYM_VALBYHND, lHdlVar, sizeof(type), (void*)&data);
    if (nErr)
        return nErr;
    return 0;
}

template <typename	type>
        long ADS_template_variable<type>::ADS_release_handler(PAmsAddr  pAddr)
{
    
    long    nErr;
    nErr = AdsSyncWriteReq(pAddr, ADSIGRP_SYM_RELEASEHND, 0, sizeof(lHdlVar), &(lHdlVar));
    lHdlVar = 0;
    return nErr;
    
}
*/











