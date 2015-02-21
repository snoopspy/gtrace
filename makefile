all: gtrace_test

gtrace_test: main.o gtrace.o
	gcc -o gtrace_test main.o gtrace.o -lpthread

clean:
	rm -rf *.o
	rm -rf gtrace_test
