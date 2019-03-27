

directory=pwd;
mex ADS_read_mex.cpp ADS_lib.cpp -LC:\Users\Admin\Desktop\ADS_beckhoff_matlab-master -lTcAdsDll
mex ADS_write_mex.cpp ADS_lib.cpp -LC:\Users\Admin\Desktop\ADS_beckhoff_matlab-master -lTcAdsDll

ADS_write_mex([10, 3, 1, 138, 3, 1],'GVL.tmp',0.5)
A=ADS_read_mex([10, 3, 1, 138, 3, 1],'GVL.tmp');