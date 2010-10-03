@echo  off

SET COMPILE_IDE = yes
path = C:\MinGW\msys\1.0\bin;%path%

make -f makefile %1