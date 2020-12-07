CPPFLAGS+=-g
#LDLIBS+=-lws2_32 # for windows

all: exam

exam: exam.o gtrace.o
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f *.o exam exam.exe
