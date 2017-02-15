close all ;
clear ;
clc ;

data = load('PLLResults.txt') ;

figure('name', 'PLL_C');
plot(data(:,1),data(:,2)) ;

figure('name', 'Error2Ceil');
plot(data(:,1), data(:,3));

figure('name', 'MeanValue');
plot(data(:,1), data(:,4));

figure('name', 'W');
plot(data(:,1), data(:,5));

figure('name', 'Sum');
plot(data(:,1), data(:,6));
