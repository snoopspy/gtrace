#define SHOW_THREAD_ID

#include <arpa/inet.h>
#include <limits.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#ifdef SHOW_THREAD_ID
#include <pthread.h>
#endif // SHOW_THREAD_ID

#define BUF_SIZE BUFSIZ
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 8908
#define INVALID_SOCK -1

typedef struct
{
	struct {
		char ip[PATH_MAX];
		uint16_t port;
	} conf;
	bool active;
	int sock;
	struct sockaddr_in addr;
} gtrace_t;

static gtrace_t _gtrace =
{
	.active = false,
};

static bool _open();
static bool _close();
static void _write(char* buf, int len);

static bool _open()
{
	if (_gtrace.active)
		return false;

	_gtrace.sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (_gtrace.sock == INVALID_SOCK)
		return false;

	_gtrace.addr.sin_family = AF_INET;
	_gtrace.addr.sin_port = htons(_gtrace.conf.port);
	_gtrace.addr.sin_addr.s_addr = inet_addr(_gtrace.conf.ip);
	memset(&_gtrace.addr.sin_zero, sizeof(_gtrace.addr.sin_zero), 0);

	_gtrace.active = true;
	return true;
}

static bool _close()
{
	if (!_gtrace.active)
		return false;

	if (_gtrace.sock != -1)
	{
		close(_gtrace.sock);
		shutdown(_gtrace.sock, 0x02); // SD_BOTH
		_gtrace.sock = INVALID_SOCK;
	}

	_gtrace.active = false;
	return true;
}

static void _write(char* buf, int len)
{
	sendto(_gtrace.sock, buf, len, 0,
		(struct sockaddr*)&_gtrace.addr, sizeof(struct sockaddr_in));
}

void gtrace(const char* fmt, ...)
{
	char* p;
	int len;
	int remn;
	int res;
	char buf[BUF_SIZE];
	va_list args;

	if (!_gtrace.active)
		return;

	p = buf;
	len = 0;
	remn = BUF_SIZE;

#ifdef SHOW_THREAD_ID
	res = snprintf(p, remn, "%08lX ", pthread_self());
	if (res < 0)
		return;
	p += res;
	len += res;
	remn -= res;
#endif // SHOW_THREAD_ID

	va_start(args, fmt);
	res = vsnprintf(p, remn, fmt, args);
	va_end(args);
	if (res < 0) return;
	p += res;
	len += res;
	remn -= res;

	_write(buf, len);
}

void gtrace_init(const char *ip, int port)
{
	if (_gtrace.active)
		_close();

	strncpy(_gtrace.conf.ip, ip, PATH_MAX);
	_gtrace.conf.port = port;

	_open();
}
