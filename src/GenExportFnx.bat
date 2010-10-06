@echo off
@sed 's/\*//g;s/const//g' QinYiprot.h | gawk -f exp.awk > QinYiExportFnx.h
echo };>> QinYiExportFnx.h
@echo on