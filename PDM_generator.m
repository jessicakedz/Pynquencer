%create pynq board pdm data file from wave file
%
% Jessica Kedziora, David Pottinger
% 8FEB2018, UCSD WES 269
clear all; close all; clc;

[fname,pname]=uigetfile('*.wav')
fullfile=strcat(pname,fname);

[Y, FS]=audioread(fullfile);

Fs=192000*8;
%resample wav file
tempo=interp(Y(:,1),floor(Fs/FS));

SampleUp=tempo(1:16*floor(length(tempo)/16));

w=tukeywin(length(SampleUp),0.01)';

x=w'.*SampleUp./max(abs(SampleUp)); 

qe=0;
  for n = 2:length(x)
      if (x(n) >= qe)
          y(n) = 1;
      else
          y(n)=-1;

      end
      qe = y(n) - x(n) + qe;
      qen(n)=qe;
  end
  y=0.5*(y+1);
  [r,c]=size(y);
 y(1)=0;
 
 yf=y;%filter(Hd,y);

  sound(decimate(double(yf)/max(double(yf)),96),2000)
  % ok to here
  
 %bits
 ya= sum(reshape(yf,16,c/16)'.*2.^[15:-1:0],2);
  writeNPY([ya;ya],strcat(fname(1:end-4),'.npy'))
  