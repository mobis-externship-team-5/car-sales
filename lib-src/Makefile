SRCS = product.c product-detail.c hash.c
OBJS = $(SRCS:.c=.o)
INCPATH = ../include
CFLAGS = -I$(INCPATH) -g -c -fPIC

all: $(OBJS)
	gcc -shared -o libcarsales.so $(OBJS)
	cp libcarsales.so ../lib

.c.o: $(SRCS)
	gcc $(CFLAGS) $*.c

clean:
	rm $(OBJS) libcarsales.so ../lib/libcarsales.so
