CC=gcc
CFLAGS+=-g
#LDLIBS+=-lws2_32 # for windows

all: exam

exam: gtrace.o exam.o
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -rf *.o exam exam.exe
