ODIR= ./bin
OUT = $(ODIR)/cube
IDIR= include
CC 	= gcc
OS := $(shell uname -s)

CFLAGS = -I$(IDIR)
LIBS=-lGL -lGLU -lglut

ifeq ($(OS),Darwin)
		LIBS=-framework OpenGL -framework GLUT
endif

_DEPS= keyboard.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJS= cube.o keyboard.o utils.o
OBJS = $(patsubst %,$(IDIR)/%,$(_OBJS))

all: inits $(OUT)

inits:
		@mkdir -p $(ODIR)
		@echo "finished pre-build initialization..."

$(ODIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

$(OUT): $(OBJS)
		gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

run:
		$(OUT)

clean: 
		rm $(IDIR)/*.o
		rm -fr $(ODIR)
