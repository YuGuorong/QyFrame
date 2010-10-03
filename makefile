.PHONY : makeoutdir  genbin genelf  clean 

include source.mak	         

OUTDIR_   = ./o
OUT_DIR   =  $(strip $(OUTDIR_))

TARGET	 = $(OUT_DIR)/AppsEntry.axf

BIN	 = $(TARGET:axf=bin)
SYMBLE_FILE = $(TARGET:axf=sym)
MAP_FILE = $(TARGET:axf=map)
GEN_LOG  = $(TARGET:axf=log)

DIR_ARM        =  c:/progra~1/arm/adsv1_2
ARCH           =  ARM9EJ-S  #ARM7EJ-S ARM926EJ-S

DIR_TOOL       =  $(DIR_ARM)/bin
DIR_TOOL       := $(strip $(DIR_TOOL))
LINK           =  $(DIR_TOOL)/armlink.exe          # Linker
CC32           =  $(DIR_TOOL)/armcc.exe
ASM            =  $(DIR_TOOL)/armasm.exe           # ARM assembler
LIB            =  $(DIR_TOOL)/armar.exe            # Library tool
BIN_CREATE     =  $(DIR_TOOL)/fromelf.exe          # Binary tool


VIAC	 = compile.txt    

VIAL	 = link.txt

POSTLINK_FLAGS = -c -output $(BIN) -bin

VIA =	  -via

OBJS = $(SRC_LIST:.c=.o)
OBJS := $(subst $(DIR_SRC),$(OUT_DIR),$(OBJS))

RM = rm 
RD = rm -rf

#RM = del /F /S /Q
#RD = rd  /S /Q
  
all:	makeoutdir genbin
  
genbin: genelf 
	@echo Begin create bin file...
	$(BIN_CREATE) $(POSTLINK_FLAGS) $(TARGET)

genelf : $(OBJS) 
	@echo create elf file.
	$(LINK) -o $(TARGET)  $(VIA) $(VIAL) $(LINKOPT) $(OBJS)
	
$(OUT_DIR)/%.o: $(DIR_SRC)/%.c
	@echo compile $< to $@ 
	$(CC32) -c -o $@ $(INCLUDES) $(VIA) $(VIAC) $(subst $(DIR_DIR),$(OUT_SRC),$<)  2>>$(GEN_LOG)

LINKOPT = -symdefs $(SYMBLE_FILE) -list $(MAP_FILE)
	
makeoutdir:
	@echo makeing output dir...
	@echo $(OBJS) 
	-@mkdir  -p  $(OUT_DIR)
	@#if not exist $(OUT_DIR) md $(OUT_DIR) | echo 创建了$(OUT_DIR)目录 
	@echo Record warnnings and error: > $(strip $(GEN_LOG))
		
	
clean :
	@echo clean all generated files.
	-@$(RM) $(OBJS) $(TARGET) $(BIN) $(SYMBLE_FILE) $(MAP_FILE)
	@#-$(RD) $(OUT_DIR)



