SRCS = $(shell find -name '*.cpp')
HDRS = $(shell find -name '*.h')
OBJS = $(addsuffix .o,$(basename $(SRCS)))

STYLEFLAGS = --style=allman --indent-classes --indent-switches

INCLUDE = -I/usr/include/ -Iinclude
LIBDIR  = -L/usr/X11R6/lib 

CC = g++
CFLAGS = -Wall $(INCLUDE)

all: $(OBJS) lib

%.o : %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

style: $(SRCS) $(HDRS)
	astyle $(STYLEFLAGS) $^

lib: $(OBJS)
	ar -rcs dasyur.a $^

clean:
	rm $(OBJS)
	rm dasyur.a

