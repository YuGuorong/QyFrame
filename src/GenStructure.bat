@echo off
@sed 's/}//g' QinYiprot.h | gawk -f s.awk >QinYiAdpStruct.h
@echo }QY_ADAPTOR; >>QinYiAdpStruct.h
@echo on