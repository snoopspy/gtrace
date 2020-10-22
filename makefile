CFLAGS+=-g

all: exam

exam: gtrace.o exam.o
	$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -rf *.o exam exam.exe
