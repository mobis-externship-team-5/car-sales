SRCS = app.c
OBJS = app.o
LDFLAGS = -L../lib -lcarsales
INCPATH = ../include
CFLAGS = -I$(INCPATH) -g -c

app: $(OBJS)
	gcc -o $@ $(OBJS) $(LDFLAGS)
app.o: app.c
	gcc $(CFLAGS) $*.c

clean:
	rm $(OBJS) app