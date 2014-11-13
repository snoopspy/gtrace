#ifndef __GTRACE_H__
#define __GTRACE_H__

#ifdef __cplusplus
extern "C" {
#endif

void gtrace(const char* fmt, ...);
void gtrace_option(const char *ip, int port);

#ifdef __cplusplus
}
#endif

#endif // __GTRACE_H__
