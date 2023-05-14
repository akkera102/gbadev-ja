@echo off
set PATH=C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

cd data

grit image1.png -ffimage1.grit
grit image2.png -ffimage2.grit
ren *.img.bin *.

gbfs ..\test.gbfs *.img
del *.img


echo done!
pause
