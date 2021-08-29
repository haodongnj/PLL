clear ;
close all ;

d = load('result.txt') ;

t = d(:, 1) ;
f = d(:, 2) ;

plot(t, f)
xlabel('Time(s)')
ylabel('Frequency(Hz)')
title('FLL response')