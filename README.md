gilgil trace version 0.1
========================


*how to use*

- include gtrace.h
- call gtrace function.
- if you would like to change gtrace config, call gtrace_init function.


*example*

	void basic_test()
	{
		gtrace("hello world");
	}

	void init_test()
	{
		gtrace_init("127.0.0.1", 8908);
		gtrace("hello world");
	}

	void init_fini_test()
	{
		gtrace_init("127.0.0.1", 8908);
		gtrace("hello world");
		gtrace_fini();
	}

