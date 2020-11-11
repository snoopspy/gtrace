CPPFLAGS+=-g
#LDLIBS+=-lws2_32 # for windows

all: exam

exam: exam.o gtrace.o
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -rf *.o exam exam.exe
