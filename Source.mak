

DIR_SRC   = ./src
DIR_SRC  := $(strip $(DIR_SRC))
DIR_MTK  = ../QinYiAppInc

SRC_LIST = $(DIR_SRC)/QyAppMain.c  \
					 $(DIR_SRC)/QyAdp.c  \
					 $(DIR_SRC)/tkc.c  \
					 $(DIR_SRC)/QinYiAppSrc.c \
					 $(DIR_SRC)/QinYiProtocol.c \
					 $(DIR_SRC)/QinYiAppAdapt.c \
					 $(DIR_SRC)/QinYiDecoder.c \
					 $(DIR_SRC)/start.c
					 
					 
INCLUDES  = -I$(DIR_SRC) -I./inc 

LIBS     = 
#./src/start.o
