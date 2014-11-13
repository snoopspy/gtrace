all: test1

test1: test1.o gtrace.o

clean:
	rm -rf *.o
	rm -rf test1
