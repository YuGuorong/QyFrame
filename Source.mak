

DIR_SRC   = ./src
DIR_SRC  := $(strip $(DIR_SRC))

SRC_LIST = $(DIR_SRC)/tkc.c \
	         $(DIR_SRC)/start.c     

INCLUDES  = -I$(DIR_SRC)
