#ifndef _ERROR_H
#define _ERROR_H

#include "apue.h"

void err_doit(const char* fmt, va_list ap);
void err_quit(const char* fmt, ...);
void err_sys(const char* fmt, ...);

#endif

