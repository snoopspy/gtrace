#include "gtrace.h"

void test1()
{
	gtrace("hello world");
}

void test2()
{
	gtrace_init("127.0.0.1", 8908);
	gtrace("hello world");
}

int main()
{
	test1();
	test2();
	return 0;
}
