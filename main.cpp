#include "gtrace.h"

int main()
{
	gtrace_init("127.0.0.1", 8908);
	gtrace("hello world\n");
	return 0;
}
