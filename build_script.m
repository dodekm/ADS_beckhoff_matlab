%skript na kompilaciu MEX funkcii a S funkcii

mex ('ADS_write_mex.cpp','ADS_lib.cpp',strcat('-L',pwd()),'-lTcAdsDll')
mex ('ADS_read_mex.cpp','ADS_lib.cpp',strcat('-L',pwd()),'-lTcAdsDll')
mex ('ADS_open_mex.cpp','ADS_lib.cpp',strcat('-L',pwd()),'-lTcAdsDll')
mex ('ADS_close_mex.cpp','ADS_lib.cpp',strcat('-L',pwd()),'-lTcAdsDll')
mex ('ADS_setup_SFUN.cpp','ADS_lib.cpp',strcat('-L',pwd()),'-lTcAdsDll')
mex ('ADS_write_SFUN.cpp','ADS_lib.cpp',strcat('-L',pwd()),'-lTcAdsDll')
mex ('ADS_read_SFUN.cpp','ADS_lib.cpp',strcat('-L',pwd()),'-lTcAdsDll')