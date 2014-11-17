gtrace version 0.1
========================


*how to use*

- include gtrace.h
- call gtrace or GTRACE function.
- if you would like to change gtrace config, call gtrace_open function.


*example*

	#include "gtrace.h"

	void gtrace_test()
	{
		gtrace("hello world");
	}

	void gtrace_conf_test()
	{
		gtrace_open("127.0.0.1", 8908);
		gtrace("hello world");
		gtrace_close();
	}

	void GTRACE_test()
	{
		GTRACE("hello world");
	}

	void GTRACE_conf_test()
	{
		gtrace_open("127.0.0.1", 8908);
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
