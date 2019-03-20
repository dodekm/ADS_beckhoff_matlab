#pragma once
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <conio.h>
#include <cstring>

#include "TcAdsDef.h"
#include "TcAdsApi.h"



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
void ADS_stop_plc(PAmsAddr  pAddr);
void ADS_start_plc(PAmsAddr  pAddr);
void ADS_init_var_INT(ADS_variable* var, const char* variable_name);
void ADS_destroy_var(ADS_variable* var);
long ADS_deinit();

