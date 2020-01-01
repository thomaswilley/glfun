/*
 * Miscellaneous utilities e.g., logging
 * (c) @thomaswilley, 2019-20
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdarg.h>

void TW_vlog (const char *cap, const char *fmt, va_list ap);
void TW_log (const char *cap, const char *fmt, ...);

#endif /* UTILS_H*/
