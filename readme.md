gtrace version 0.2
==================

# How to use

  * Include **gtrace.h** and add **gtrace.c** in your project.
  * Call **gtrace**(function) or **GTRACE**(macro).
  * If you would like to change option, call **gtrace_open** function.

# Example

```cpp
#include "gtrace.h"

void gtrace_test()
{
  gtrace("hello world 1");
}

void gtrace_conf_test()
{
  gtrace_open("127.0.0.1", 8908, true);
  gtrace("hello world 2");
  gtrace_close();
}

void GTRACE_test()
{
  GTRACE("hello world 3");
}

void GTRACE_conf_test()
{
  gtrace_open("127.0.0.1", 8908, true);
  GTRACE("hello world 4");
  gtrace_close();
}

int main()
{
  gtrace_test();
  gtrace_conf_test();
  GTRACE_test();
  GTRACE_conf_test();
  return 0;
}
```

# Output
```
7FE81376A740 hello world 1
7FE81376A740 hello world 2
7FE81376A740 [exam.cpp:17] GTRACE_test hello world 3
7FE81376A740 [exam.cpp:23] GTRACE_conf_test hello world 4
```

# For mingw

  * You can build example in the following make option.
```
make CC=gcc LDFLAGS+=-lws2_32
```