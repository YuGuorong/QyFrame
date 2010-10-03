

DIR_SRC   = ./src
DIR_SRC  := $(strip $(DIR_SRC))

SRC_LIST = $(DIR_SRC)/QyAppMain.c  \
					 $(DIR_SRC)/tkc.c  \
					 
					 
INCLUDES  = -I$(DIR_SRC) -I./inc

LIBS     = ./src/start.o
