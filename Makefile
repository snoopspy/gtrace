LDFLAGS +=-lpthread

all: example1 example2

example1: example1.o gtrace.o

example2: example2.o gtrace.o

clean:
	rm -rf *.o
	rm -rf example1
	rm -rf example2

