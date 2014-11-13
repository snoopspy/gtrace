#include "gtrace.h"

int main()
{
	gtrace_open("127.0.0.1", 8908);
	gtrace("hello world");
	gtrace_close();
	return 0;
}

