
% combines files in binary combinations
clear all;close all; clc;
% resample

N=5; %number of instrument. 

df=2^(1/12) % 1/2 step increment


Fs=44e3;
Tmax=0.3;
t=0:1/Fs:Tmax-(1/Fs);

f=440;
%w=window(@rectwin  ,4*length(t))';
w=tukeywin(length(t),0.03)';

%example data, replacewith files
tone(1,:)=real(exp(-j*2*pi*f*t));
tone(2,:)=real(exp(-j*2*pi*f*t).*exp(-j*2*pi*t*(f*3*df-f)));
tone(3,:)=real(exp(-j*2*pi*f*t).*exp(-j*2*pi*t*(f*6*df-f)));
tone(4,:)=real(exp(-j*2*pi*f*t).*exp(-j*2*pi*t*(f*9*df-f)));
tone(5,:)=real(exp(-j*2*pi*f*t).*exp(-j*2*pi*t*(f*12*df-f)));

%generate combination matrix
index_array=(repmat([1:N],2^N,1)'.*(1*(dec2bin(0:(2^N-1))')-48));
[r,c]=size(index_array);

%generate selection indices
for ii=1:c
    
    file_mask=unique(index_array(find(index_array(:,ii)),ii));
    file(ii).mask=file_mask;
end

%combine files
for ii=1:c
    file(ii).sound=w.*sum(tone(file(ii).mask,:),1);
    
end

sound(file(30).sound)