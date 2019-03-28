

mex ADS_read_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
mex ADS_write_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll

%mex ADS_read_mex.cpp ADS_lib.cpp -LC:\Users\Admin\Desktop\ADS_beckhoff_matlab-master -lTcAdsDll
%mex ADS_write_mex.cpp ADS_lib.cpp -LC:\Users\Admin\Desktop\ADS_beckhoff_matlab-master -lTcAdsDll

%ADS_write_mex([10, 3, 1, 138, 3, 1],'GVL.tmp',TC_INT_type,0.5)
%A=ADS_read_mex([10, 3, 1, 138, 3, 1],'GVL.tmp',TC_INT_type);








