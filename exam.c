#include "gtrace.h"

void gtrace_test()
{
  gtrace("hello world 1");
}

void gtrace_conf_test()
{
  gtrace_open("127.0.0.1", 8908, true);
  gtrace("hello world 2");
  gtrace_close();
}

void GTRACE_test()
{
  GTRACE("hello world 3");
}

void GTRACE_conf_test()
{
  gtrace_open("127.0.0.1", 8908, true);
  GTRACE("hello world 4");
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
