gtrace version 0.4
==================

# How to use

* Include **gtrace.h** and add **gtrace.c** in your project.
* Call **gtrace**(function) or **GTRACE**(macro).
* If you would like to change option, call **gtrace_close** and **gtrace_open** function.


# Options
```
bool gtrace_open(const char* ip, int port, bool so /*stdout*/, const char* file);
```

|options|description|
|---|---|
|ip, port|udp sending options. if ip is nullptr(0) or port is 0, udp sending is disabled.|
|so|stdout write option.|
|file|file writing option. if file is nullptr(0), file writing is disabled.|

# Example

```cpp
#include "gtrace.h"

void simple_test() {
	for (int i = 0; i < 5; i++)
		GTRACE("hello world(simple) %d\n", i);
}

void udp_test() {
	gtrace_close();
	gtrace_open("127.0.0.1", 8908, false, 0);
	GTRACE("hello world(udp)");
}

void stdout_test() {
	gtrace_close();
	gtrace_open(0, 0, true, 0);
	GTRACE("hello world(stdout)\n");
}

void file_test() {
	gtrace_close();
	gtrace_open(0, 0, false, "test.log");
	GTRACE("hello world(file)\n");
}

int main() {
	simple_test();
	udp_test();
	stdout_test();
	file_test();
}
```

# Output

## stdout
```
$ ./exam
7F23E7D41540 [exam.c:5] simple_test hello world(simple) 0
7F23E7D41540 [exam.c:5] simple_test hello world(simple) 1
7F23E7D41540 [exam.c:5] simple_test hello world(simple) 2
7F23E7D41540 [exam.c:5] simple_test hello world(simple) 3
7F23E7D41540 [exam.c:5] simple_test hello world(simple) 4
7F23E7D41540 [exam.c:17] stdout_test hello world(stdout)
```

## file(test.log)
```
$ tail -f test.log
7F23E7D41540 [exam.c:23] file_test hello world(file)
```

## udp server
```
$ ./us 8908
7F2341BC5540 [exam.c:5] simple_test hello world(simple) 0
7F2341BC5540 [exam.c:5] simple_test hello world(simple) 1
7F2341BC5540 [exam.c:5] simple_test hello world(simple) 2
7F2341BC5540 [exam.c:5] simple_test hello world(simple) 3
7F2341BC5540 [exam.c:5] simple_test hello world(simple) 4
7F2341BC5540 [exam.c:11] udp_test hello world(udp)
```

# For mingw

* You can build example in the following make option.
```
make CC=gcc LDFLAGS+=-lws2_32
```
