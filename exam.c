#include "gtrace.h"

void simple_test() {
	for (int i = 0; i < 5; i++)
		GTRACE("hello world(simple) %d", i);
}

void udp_test() {
	gtrace_close();
	gtrace_open("127.0.0.1", 8908, false, 0);
	GTRACE("hello world(udp)");
}

void stderr_test() {
	gtrace_close();
	gtrace_open(0, 0, true, 0);
	GTRACE("hello world(stderr)");
}

void file_test() {
	gtrace_close();
	gtrace_open(0, 0, false, "test.log");
	GTRACE("hello world(file)");
}

int main() {
	gtrace_default("127.0.0.1", 8908, true, 0);
	simple_test();
	udp_test();
	stderr_test();
	file_test();
}
