// ----------------------------------------------------------------------------
//
// gtrace version 0.9
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#ifndef __GTRACE_H__
#define __GTRACE_H__

#ifdef __cplusplus
extern "C" {
#endif

void gtrace(const char* fmt, ...) __attribute__ ((format (printf, 1, 2)));
void gtrace_fini();
void gtrace_init(const char *ip, int port);

#ifdef __cplusplus
}
#endif

#endif // __GTRACE_H__
