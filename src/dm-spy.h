#ifndef _dm_spy_h_
#define _dm_spy_h_

#include "dryos.h"

void debug_intercept();
int debug_intercept_running();

void debug_logstr(const char * str);
void debug_loghex(uint32_t x);
void debug_loghex2(uint32_t x, int digits);
#endif // _dm_spy_h_
