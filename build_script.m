
TC_BOOL_type=0
TC_BYTE_type=1
TC_WORD_type=2
TC_DWORD_type=3
TC_INT_type=4
TC_DINT_type=5
TC_LINT_type=6
TC_USINT_type=7
TC_UINT_type=8
TC_UDINT_type=9
TC_ULINT_type=10
TC_REAL_type=11
TC_LREAL_type=12

directory=pwd;

mex ADS_read_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
mex ADS_write_mex.cpp ADS_lib.cpp -Lx:\Dropbox\FEI\OP\ADS_beckhoff_matlab -lTcAdsDll
%%
%ADS_write_mex([10, 3, 1, 138, 3, 1],'GVL.tmp',TC_INT_type,0.5)
%A=ADS_read_mex([10, 3, 1, 138, 3, 1],'GVL.tmp',TC_INT_type);

pause on 

Tvz=1/10;
T_mer=10;
N=floor(T_mer/Tvz);

y=zeros(1,N);
u=zeros(1,N);

for i=1:N

    u(i)=10;
    ADS_write_mex([10, 3, 1, 138, 3, 1],'GVL.ventilator',TC_INT_type,u(i));
    y(i)=ADS_read_mex([10, 3, 1, 138, 3, 1],'GVL.snimac1',TC_INT_type);
    pause(Tvz);

end





