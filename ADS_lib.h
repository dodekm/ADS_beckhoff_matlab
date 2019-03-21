#pragma once
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <cstring>

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
	char					name[20];
	void*					data_pointer;
	TC_type					data_type;
	unsigned long			data_type_size;

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



unsigned long type_size(TC_type data_type);

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
void ADS_stop_plc(PAmsAddr  pAddr);
void ADS_start_plc(PAmsAddr  pAddr);
void ADS_init_var_INT(ADS_variable* var, const char* variable_name, TC_type data_type);
void ADS_destroy_var(ADS_variable* var);
long ADS_deinit();

