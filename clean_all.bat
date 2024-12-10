@echo off
set PATH=c:\devkitPro\msys2\usr\bin;C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

for /d %%i in (.\*) do (
	pushd "%%i"
	echo %%i
	make clean
	popd
)

pause
