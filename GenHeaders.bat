pushd .

CD ..\QinYiAppInc

cd src

@rem path = C:\MinGW\msys\1.0\bin;%path%

@gawk -f s.awk QinYiprot.h  >QinYiAdpStruct.h
@echo }QY_ADAPTOR; >>QinYiAdpStruct.h

@sed 's/\*//g;s/const//g' QinYiprot.h | gawk -f qydef.awk > QinYiFnxDef.h

@sed 's/\*//g;s/const//g' QinYiprot.h | gawk -f exp.awk > QinYiExportFnx.h
@rem  @echo  >> QinYiExportFnx.h

@echo on
