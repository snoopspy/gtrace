#define SHOW_THREAD_ID

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#ifdef WIN32
#include <winsock2.h>
#endif // WIN32
#ifdef __linux__
#include <arpa/inet.h>
#endif // __linux__

#ifdef SHOW_THREAD_ID
#include <pthread.h>
#endif // SHOW_THREAD_ID

#include "gtrace.h"

typedef struct {
	struct {
#ifdef __cplusplus
		bool configured{false};
		bool active{false};
#else
		bool configured;
		bool active;
#endif // __cplusplus
	} status;

	struct {
		bool enabled;
		int sock;
		struct sockaddr_in addr;
	} udp;

	//
	// stderr
	//
	struct {
		bool enabled;
	} se;

	//
	// file
	//
	struct {
		bool enabled;
		FILE* fp;
	} file;
} gtrace_t;

#ifdef __cplusplus
gtrace_t _gtrace;
#else
gtrace_t _gtrace = {
	.status.configured = false,
	.status.active = false
};
#endif

#define BUF_SIZE 8192
// ----------------------------------------------------------------------------
// api
// ----------------------------------------------------------------------------
void gtrace(const char* fmt, ...) {
	if (!_gtrace.status.configured) {
		_gtrace.status.configured = true;
		bool file_load = false;
		FILE* fp = fopen("gtrace.conf", "r");
		if (fp != NULL) {
			char ip[BUF_SIZE];
			int port;
			int se;
			char file[BUF_SIZE];
			int res = fscanf(fp, "%s %d %d %s", ip, &port, &se, file);
			if (res >=2 && res <= 4) {
				switch (res) {
					case 2: gtrace_open(ip, port, false, NULL); break;
					case 3: gtrace_open(ip, port, (bool)se, NULL); break;
					case 4: gtrace_open(ip, port, (bool)se, file); break;
				}
				file_load = true;
			}
		}
		if (!file_load)
			gtrace_open("127.0.0.1", 8908, true, NULL);
	}

	if (!_gtrace.status.active)
		return;

	int res;
	char buf[BUF_SIZE + 1];// gilgil temp
	char* p = buf;
	int len = 0;
	ssize_t remn = BUF_SIZE;
	memset(buf, 'a', BUF_SIZE + 1); // gilgil temp

	struct timeval now;
	struct tm* local;
	gettimeofday(&now, NULL);
	local = localtime(&now.tv_sec);
	res = snprintf(p, remn, "%02d%02d%02d %02d%02d%02d-%03lu ",
		(local->tm_year) % 100, local->tm_mon + 1, local->tm_mday,
		 local->tm_hour, local->tm_min, local->tm_sec, now.tv_usec / 1000);
	if (res < 0) {
		fprintf(stderr, "time: snprintf return %d\n", res);
		return;
	}
	p += res; len += res; remn -= res;	
	if (remn <= 0) {
		fprintf(stderr, "time: not enough buffer size res=%d len=%d\n", res, len);
		return;
	}

#ifdef SHOW_THREAD_ID
	pthread_t id = pthread_self() & 0xFFFF;
	res = snprintf(p, remn, "%04lX ", id);
	if (res < 0) {
		fprintf(stderr, "thread: snprintf return %d\n", res);
		return;
	}
	p += res; len += res; remn -= res;
	if (remn <= 0) {
		fprintf(stderr, "thread: not enough buffer size res=%d len=%d\n", res, len);
		return;
	}
#endif // SHOW_THREAD_ID

	va_list args;
	va_start(args, fmt);
	res = vsnprintf(p, remn, fmt, args);
	va_end(args);
	if (res < 0) {
		fprintf(stderr, "vsnprintf: snprintf return %d\n", res);
		return;
	}
	p += res; len += res; remn -= res;
	if (remn <= 0) {
		fprintf(stderr, "vsprintf: not enough buffer size res=%d len=%d\n", res, len);
		return;
	}

	memcpy(p, "\n\0", 2);
	res = 0;
	p += res; len += res; remn -= res;
	if (remn <= 0) {
		fprintf(stderr, "linefeed: not enough buffer size res=%d len=%d\n", res, len);
		return;
	}

	if (_gtrace.udp.enabled)
		sendto(_gtrace.udp.sock, buf, len, 0, (struct sockaddr*)&_gtrace.udp.addr, sizeof(struct sockaddr_in));

	if (_gtrace.se.enabled) {
		fprintf(stderr, "%s", buf);
	}

	if (_gtrace.file.enabled) {
		fprintf(_gtrace.file.fp, "%s", buf);
		fflush(_gtrace.file.fp);
	}
}

bool gtrace_open(const char* ip, int port, bool se, const char* file) {
	_gtrace.status.configured = true;
	if (_gtrace.status.active)
		return false;

#ifdef WIN32
	static bool first = true;
	if (first) {
		WSADATA wsaData;
		WSAStartup(0x0202, &wsaData);
		first = false;
	}
#endif // WIN32

	//
	// udp
	//
	_gtrace.udp.enabled = false;
	if (ip != NULL && port != 0) {
		_gtrace.udp.sock = socket(AF_INET, SOCK_DGRAM, 0);
		if (_gtrace.udp.sock == -1) {
			fprintf(stderr, "socket return nullptr\n");
		} else {
			_gtrace.udp.addr.sin_family = AF_INET;
			_gtrace.udp.addr.sin_port = htons(port);
			_gtrace.udp.addr.sin_addr.s_addr = inet_addr(ip);
			memset(&_gtrace.udp.addr.sin_zero, 0, sizeof(_gtrace.udp.addr.sin_zero));
			_gtrace.udp.enabled = true;
		}
	}

	//
	// stderr
	//
	_gtrace.se.enabled = false;
	if (se == true) {
		_gtrace.se.enabled = true;
	}

	//
	// file
	//
	_gtrace.file.enabled = false;
	if (file != NULL) {
		_gtrace.file.fp = fopen(file, "a");
		if (_gtrace.file.fp == NULL) {
			fprintf(stderr, "fopen(%s) return nullptr\n", file);
		} else {
			_gtrace.file.enabled = true;
		}
	}

	_gtrace.status.active = true;
	return true;
}

bool gtrace_close(void) {
	_gtrace.status.configured = true;
	if (!_gtrace.status.active)
		return false;

	if (_gtrace.udp.enabled) {
		if (_gtrace.udp.sock != -1) {
			close(_gtrace.udp.sock);
			shutdown(_gtrace.udp.sock, 0x02); /* SD_BOTH */
			_gtrace.udp.sock = -1;
		}
	}

	if (_gtrace.se.enabled) {
	}

	if (_gtrace.file.enabled) {
		if (_gtrace.file.fp != NULL) {
			fclose(_gtrace.file.fp);
			_gtrace.file.fp = NULL;
		}
	}

	_gtrace.status.active = false;
	return true;
}

// ----------------------------------------------------------------------------
// macro
// ----------------------------------------------------------------------------
const char* gtrace_file_name(const char* file_name) {
#ifdef WIN32
	const char* p1 = strrchr(file_name, '\\');
	const char* p2 = strrchr(file_name, '/');
	const char* p	= p1 > p2 ? p1 : p2;
#endif // WIN32
#ifdef __linux__
	const char* p = strrchr(file_name, '/');
#endif // __linux__
	return (p == NULL ? file_name : p + 1);
}

const char* gtrace_func_name(const char* func_name) {
#ifdef WIN32
	const char* p = strrchr(func_name, ':');
	return (p == NULL ? func_name : p + 1);
#endif // WIN32
#ifdef __linux__
	return func_name;
#endif // __linux__
}
