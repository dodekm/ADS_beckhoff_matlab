
%skript na kompilaciu MEX funkcii a S funkcii
%je nutne rucne zmenit linkovaci adresar na aktualny pracovny prieconok
pwd
mex ADS_read_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
mex ADS_write_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
mex ADS_open_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
mex ADS_close_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll

mex ADS_read_SFUN.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
mex ADS_write_SFUN.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
mex ADS_setup_SFUN.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll

