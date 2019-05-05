
%skript na demonstraciu pouzitia MEX funkcii pre citanie a zapis premennych

clear all;
close all;

TC_data_types
pause on 

Tvz=1/10;
T_mer=10;
N=floor(T_mer/Tvz);

y=zeros(1,N);
u=zeros(1,N);
t=zeros(1,N);

spirala_in=20000;
ventilator_in=20000;

ADS_open_mex();

ventilator_name='GVL.ventilator';
spirala_name='GVL.spirala';
snimac_name='GVL.snimac';

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




