
SRC=$(wildcard *.c)
OBJS=$(SRC:%.c=%.o)

CFLAGS=-Iinclude -fPIC

LD_LIBS=-ldmalloc -lm -lc
AR=ar -r
RANLIB=ranlib

libtidy.a: $(OBJS)
	$(AR) $@ $(OBJS) 
	if test -n "$(RANLIB)" ; then $(RANLIB) $@ ; fi


