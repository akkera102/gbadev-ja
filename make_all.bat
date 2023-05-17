@echo off
set PATH=C:\devkitPro\devkitARM\bin;C:\devkitPro\tools\bin;%PATH%

for /d %%i in (.\*) do (
	pushd "%%i"
	echo %%i
	make
	popd
)

pause
