#include "utils.h"
#include <stdlib.h>

#include <stdio.h>

void TW_vlog (const char *cap, const char *fmt, va_list ap)
{
  if (cap) {
    fprintf(stderr, "%s: ", cap);
  }    

  vfprintf(stderr, fmt, ap); 
}

void TW_log (const char *cap, const char *fmt, ...) 
{
  va_list ap;

  va_start (ap, fmt);
  TW_vlog (cap, fmt, ap); 
  va_end (ap);
}
