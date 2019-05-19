clear ;
close all ;

d = load('test_fll.txt') ;

t = d(:, 1) ;
f = d(:, 2) ;

plot(t, f)