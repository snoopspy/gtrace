#include "gtrace.h"

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

int main()
{
	basic_test();
	init_test();
	init_fini_test();
	return 0;
}

