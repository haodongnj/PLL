clear ;
close all ;

load('test_sogi_qsg.txt')
sine_wave = test_sogi_qsg(:, 1) ;
phase_wave = test_sogi_qsg(:, 2) ;
sine_detect = test_sogi_qsg(:,3);
angle_freq = test_sogi_qsg(:,4) ;

plot(sine_wave);
hold on;
plot(sine_detect);
hold off ;

figure 
plot(phase_wave) ;

figure
plot(angle_freq/(2 * pi)) ;