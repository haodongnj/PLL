clear ;
close all ;

data = load('result.txt');
sine_wave = data(:, 1) ;
phase_wave = data(:, 2) ;
sine_detect = data(:,3);
angle_freq = data(:,4) ;
t = data(:,5);

plot(t, sine_wave);
hold on;
plot(t, sine_detect);
xlabel('Time(s)');
ylabel('Signal');
hold off;

figure 
plot(t, phase_wave) ;
xlabel('Time(s)');
ylabel('Phase(rad)');

figure
plot(t, angle_freq/(2 * pi)) ;
xlabel('Time(s)');
ylabel('Frequency(Hz)');