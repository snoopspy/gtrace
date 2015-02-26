all: gtrace_test

gtrace_test:
	gcc -c gtrace.c
	g++ -c exam.cpp
	gcc -o gtrace_test exam.o gtrace.o -lpthread -lws2_32

clean:
	rm -rf *.o
	rm -rf *.pro.user
	rm -rf gtrace_test
	rm -rf gtrace_test.exe
