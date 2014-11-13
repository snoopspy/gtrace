#include "gtrace.h"

int main()
{
	gtrace_option("127.0.0.1", 8908);
	gtrace("hello world\n");
}
