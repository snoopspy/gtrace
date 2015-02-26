all: gtrace_test

gtrace_test: exam.o gtrace.o
	gcc -o gtrace_test exam.o gtrace.o -lpthread

clean:
	rm -rf *.o
	rm -rf *.pro.user
	rm -rf gtrace_test
