#include <stdbool.h>
#include <sys/socket.h>

typedef struct
{
	bool active;
	int handle;
	struct sockaddr addr;

	char ip[256];
	int  port;
} gtrace_t;

gtrace_t _gtrace =
{
	false, // active
	-1,    // handle
	0,     // addr
	0,     // ip
	0      // port
};

static bool _init();
static bool _open();
static bool _close();
static void _write(char* buf, int len);

static bool _init()
{
	if (_gtrace.active) return false;
}

static bool _open()
{

}
static bool _close()
{

}
static void _write(char* buf, int len)
{

}

void gtrace(const char* fmt, ...)
{

}

void gtrace_option(const char *ip, int port)
{

}
