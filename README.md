gilgil trace version 0.1

[how to use]
Include gtrace.h
Call gtrace function.
If you would like to change gtrace config, call gtrace_init functio.

[example]
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

