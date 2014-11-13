all: test

test: main.o gtrace.o
	g++ -o test main.o gtrace.o

clean:
	rm -rf *.o
	rm -rf test

