gtrace version 0.4
==================

# How to use

* Include **gtrace.h** and add **gtrace.cpp** in your project.
* You can also use **gtrace.c** by renaming **gtrace.cpp**.
* Call **gtrace**(function) or **GTRACE**(macro).
* If you would like to change option, call **gtrace_close** and **gtrace_open** function.


# Options
```
bool gtrace_open(const char* ip, int port, bool so /*stdout*/, const char* file);
```

|options|description|
|---|---|
|ip, port|udp sending options. if ip is nullptr(0) or port is 0, udp sending is disabled. default "127.0.0.1" 8908|
|so|stdout write option. default true|
|file|file writing option. if file is nullptr(0), file writing is disabled. default nullptr(0)|

# Example

```c
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
201023 211149-323 F540 [exam.c:5] simple_test hello world(simple) 0
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 1
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 2
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 3
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 4
201023 211149-324 F540 [exam.c:17] stdout_test hello world(stdout)
```

## file(test.log)
```
$ tail -f test.log
201023 211149-324 F540 [exam.c:23] file_test hello world(file)
```

## udp server
```
$ ./us 8908
201023 211149-323 F540 [exam.c:5] simple_test hello world(simple) 0
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 1
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 2
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 3
201023 211149-324 F540 [exam.c:5] simple_test hello world(simple) 4
201023 211149-324 F540 [exam.c:11] udp_test hello world(udp)
```

# For mingw

* You can build example in the following make option.
```
LDLIBS+=-lws2_32
```
