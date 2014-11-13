gilgil trace version 0.1
========================


*how to use*

- include gtrace.h
- call gtrace function.
- if you would like to change gtrace config, call gtrace_open function.


*example1*

	int main()
	{
		gtrace("hello world");
		return 0;
	}


*example2*

	int main()
	{
		gtrace_open("127.0.0.1", 8908);
		gtrace("hello world");
		gtrace_close();
		return 0;
	}

