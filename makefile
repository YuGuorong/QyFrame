.PHONY : makeoutdir  cpheader  genbin genelf  clean 

CDEFINE  = 
include source.mak	         

OUTDIR_   = ./o
OUT_DIR   =  $(strip $(OUTDIR_))
CDEFINE  += -D QY_PIKE_PROJ 

TARGET	 = $(OUT_DIR)/AppsEntry.axf

BIN	 = $(TARGET:axf=bin)
SYMBLE_FILE = $(TARGET:axf=sym)
MAP_FILE = $(TARGET:axf=map)
GEN_LOG  = $(TARGET:axf=log)

DIR_DEP  = $(OUT_DIR)  #./dep

DIR_ARM        =  c:/progra~1/arm/adsv1_2
ARCH           =  ARM9EJ-S  #ARM7EJ-S ARM926EJ-S

DIR_TOOL       =  $(DIR_ARM)/bin
DIR_TOOL       := $(strip $(DIR_TOOL))
LINK           =  $(DIR_TOOL)/armlink.exe          # Linker
CC32           =  $(DIR_TOOL)/armcc.exe
ASM            =  $(DIR_TOOL)/armasm.exe           # ARM assembler
LIB            =  $(DIR_TOOL)/armar.exe            # Library tool
BIN_CREATE     =  $(DIR_TOOL)/fromelf.exe          # Binary tool

GCC   = gcc

VIAC	 = compile.txt    

VIAL	 = link.txt

POSTLINK_FLAGS = -c -output $(BIN) -bin

VIA =	  -via

OBJS = $(SRC_LIST:.c=.o)
OBJS := $(subst $(DIR_SRC),$(OUT_DIR),$(OBJS))

DEPS =  $(OBJS:.o=.d)
#DEPS :=  $(subst $(DIR_SRC),$(OUT_DIR),$(DEPS))

RM = rm -f
RD = rm -rf

#RM = del /F /S /Q
#RD = rd  /S /Q
  
all:	makeoutdir cpheader genbin
  
genbin: genelf 
	@echo Begin create bin file...
	$(BIN_CREATE) $(POSTLINK_FLAGS) $(TARGET)

genelf : $(OBJS) 
	@echo create elf file.
	$(LINK) -o $(TARGET)  $(VIA) $(VIAL) $(LINKOPT) $(OBJS) $(LIBS)
	
include  $(DEPS)
	
./$(OUT_DIR)/%.d: ./$(DIR_SRC)/%.c
	@echo Generating dependency $@ of $< \
	-set -e; \
	$(RM)  $@; \
	$(GCC) -MM -c $(INCLUDES) $< > $@.$$$$; \
	sed -e 's,^\($*\)\.o[ :]*,\1.o .\/$@ : ,' -e "1s/^/.\/o\//" < $@.$$$$ > $@; \
	$(RM) $@.$$$$
		
./$(OUT_DIR)/%.o: ./$(DIR_SRC)/%.c
	@echo compile $< to $@ 
	$(CC32) -c -o $@ $(INCLUDES) $(VIA) $(VIAC) $(subst $(DIR_DIR),$(OUT_SRC),$<)  #2>>$(GEN_LOG)

LINKOPT = -symdefs $(SYMBLE_FILE) -list $(MAP_FILE)
	
makeoutdir:
	@echo makeing output dir... $(DEPS)
	-@mkdir  -p  $(OUT_DIR)
	@#if not exist $(OUT_DIR) md $(OUT_DIR) | echo 创建了$(OUT_DIR)目录 
	@echo Record warnnings and error: > $(strip $(GEN_LOG))
		
cpheader: $(DIR_SRC)/QinYiprot.h

$(DIR_SRC)/QinYiprot.h: $(DIR_MTK)/QinYiprot.h 	

	
clean :
	@echo clean all generated files.
	-@$(RM) $(OBJS) $(TARGET) $(BIN) $(SYMBLE_FILE) $(MAP_FILE) $(DEPS) $(GEN_LOG)
	@#-$(RD) $(OUT_DIR)



