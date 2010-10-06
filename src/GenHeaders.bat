
@sed 's/}//g' QinYiprot.h | gawk -f s.awk >QinYiAdpStruct.h
@echo }QY_ADAPTOR; >>QinYiAdpStruct.h

@sed 's/\*//g;s/const//g' QinYiprot.h | gawk -f qydef.awk > QinYiFnxDef.h

@sed 's/\*//g;s/const//g' QinYiprot.h | gawk -f exp.awk > QinYiExportFnx.h
@echo };>> QinYiExportFnx.h

@echo on
