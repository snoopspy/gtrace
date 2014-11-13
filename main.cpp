#include "gtrace.h"

int main()
{
	gtrace_init("127.0.0.1", 8908);
	gtrace("hello world %d", 999);
	return 0;
}
