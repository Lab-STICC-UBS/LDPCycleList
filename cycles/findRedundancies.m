

% This script verify if there is no redundancy of any cycle in the file 
% by processing the FFT of each cycles and comparing with others


close all
clear all
clc

C=load("./cycle20.txt");
[nbcy, lenght]=size(C)
C=C(:,1:lenght-1);

FFTC=fft(C(1,:));

for i = 2:nbcy
  FFTC=[FFTC ; fft(C(i,:))];
end
disp("fft done")

for i = 1:nbcy-1
  for j = i+1:nbcy
    if sum(abs(FFTC(i,:))-abs(FFTC(j,:))) == 0
      disp("REDONDANCY")
    end
  end
end
disp("done!")



%C1=[1 2 2 1 1 4 3 3];
%C2=[1 1 2 2 1 3 3 4];
%tab12=[fft(C1);fft(C2)];
%IsSame12=sum(abs(tab12(1,:))-abs(tab12(2,:)))
%
%C3=[1 1 2 2 1 4 3 3];
%C4=[1 1 2 2 1 3 3 4];
%tab34=[fft(C3);fft(C4)];
%IsSame34=sum(abs(tab34(1,:))-abs(tab34(2,:)))
%
%C5=[1 1 2 2 1 1 2 2];
%C6=[1 1 2 2 1 3 3 4];
%tab56=[fft(C5);fft(C6)];
%IsSame56=sum(abs(tab56(1,:))-abs(tab56(2,:)))