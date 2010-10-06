@echo off
@sed 's/\*//g;s/const//g' QinYiprot.h | gawk -f qydef.awk > QinYiFnxDef.h
@echo on