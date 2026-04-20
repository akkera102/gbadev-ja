@echo off

exe\sox -D wav\2_23_AM.wav -c1 -b8 -e signed-integer 16384.raw trim 0 60 fade t 0 60 2 rate -v 16384 norm -1

exe\sox -D wav\2_23_AM.wav -c1 -b16 13379.wav trim 0 60 fade t 0 60 2 rate -v 13379 norm -1
exe\wav28ad 13379.wav 13379.8ad

set PATH=C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%
gbfs ..\test.gbfs *.8ad *.raw


del 16384.raw
del 13379.wav
del 13379.8ad
del decomp.wav


pause
