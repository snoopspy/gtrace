GTRACE
===

# How to use

* Include **gtrace.h** and add **gtrace.cpp** in your project.
* You can also use **gtrace.c** by renaming **gtrace.cpp**.
* Call **gtrace**(function) or **GTRACE**(macro).
* If you would like to change option, call **gtrace_default** or **gtrace_open** function.
* You can download us(udp server) in [https://gitlab.com/gilgil/scs.git](https://gitlab.com/gilgil/scs.git).

# Options
```
bool gtrace_default(const char* ip, int port, bool se /*stderr*/, const char* file);
```

|options|description|
|---|---|
|ip, port|udp sending options. if ip is nullptr(0) or port is 0, udp sending is disabled. default "127.0.0.1" 8908|
|se|stderr write option. default true|
|file|file writing option. if file is nullptr(0), file writing is disabled. default nullptr(0)|

# Example

```c
#include "gtrace.h"

void simple_test() {
	for (int i = 0; i < 5; i++)
		GTRACE("hello world(simple) %d", i);
}

void udp_test() {
	gtrace_close();
	gtrace_open("127.0.0.1", 8908, false, 0);
	GTRACE("hello world(udp)");
}

void stderr_test() {
	gtrace_close();
	gtrace_open(0, 0, true, 0);
	GTRACE("hello world(stderr)");
}

void file_test() {
	gtrace_close();
	gtrace_open(0, 0, false, "test.log");
	GTRACE("hello world(file)");
}

int main() {
	gtrace_default("127.0.0.1", 8908, true, 0);
	simple_test();
	udp_test();
	stderr_test();
	file_test();
}
```

# Output

## udp server
```
$ us 8908
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 0
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 1
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 2
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 3
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 4
201208 010941-348 D540 [exam.c:11] udp_test hello world(udp)
```

## stderr
```
$ ./exam
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 0
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 1
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 2
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 3
201208 010941-348 D540 [exam.c:5] simple_test hello world(simple) 4
201208 010941-348 D540 [exam.c:17] stderr_test hello world(stderr)
```

## file(test.log)
```
$ tail -f test.log
201208 010941-348 D540 [exam.c:23] file_test hello world(file)
```

# For mingw

* You can build example in the following make option.
```
LDLIBS+=-lws2_32
```
