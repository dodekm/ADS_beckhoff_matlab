
%skript na demonstraciu pouzitia MEX funkcii pre citanie a zapis premennych

clear all;
close all;

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

pause on 

ventilator_name='GVL.ventilator';
spirala_name='GVL.spirala';
snimac_name='GVL.snimac';

Tvz=1/10;
T_mer=10;
N=floor(T_mer/Tvz);

y=zeros(1,N);
u=zeros(1,N);
t=zeros(1,N);

ADS_open_mex();

spirala_in=20000;
ventilator_in=20000;

for i=1:N

    t(i)=i*Tvz;
    u(i)=30000*spirala_in;
    ADS_write_mex([10, 3, 1, 138, 3, 1],ventilator_name,TC_INT_type,ventilator_in);
    ADS_write_mex([10, 3, 1, 138, 3, 1],spirala_name,TC_INT_type,u(i));
    y(i)=ADS_read_mex([10, 3, 1, 138, 3, 1],snimac_name,TC_INT_type);
    pause(Tvz);

end

ADS_write_mex([10, 3, 1, 138, 3, 1],ventilator_name,TC_INT_type,0);
ADS_write_mex([10, 3, 1, 138, 3, 1],spirala_name,TC_INT_type,0);
ADS_close_mex();
figure(); 
plot(t,y,'LineWidth',2)
hold on
plot(t,u,'LineWidth',2)
xlabel('time');
ylabel('raw INT value');
legend('snimac','spirala');
title('Prechodovka merana cez ADS')
grid on;




