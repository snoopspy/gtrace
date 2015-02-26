gtrace version 0.2
==================

# How to use

  * Include gtrace.h and add gtrace.c in your project.
  * Call gtrace(function) or GTRACE(macro).
  * If you would like to change option, call gtrace_open function.

# Example

```
#include "gtrace.h"

void gtrace_test()
{
	gtrace("hello world");
}

void gtrace_conf_test()
{
	gtrace_open("127.0.0.1", 8908, true);
	gtrace("hello world");
	gtrace_close();
}

void GTRACE_test()
{
	GTRACE("hello world");
}

void GTRACE_conf_test()
{
	gtrace_open("127.0.0.1", 8908, true);
	GTRACE("hello world");
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
7F4F8FF90740 hello world
7F4F8FF90740 hello world
7F4F8FF90740 [main.cpp:17] GTRACE_test hello world
7F4F8FF90740 [main.cpp:23] GTRACE_conf_test hello world
```
