#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define _CONCAT(a, b) a ## b
#define CONCAT(a, b) _CONCAT(a, b)
#define VAR_NAME(var) CONCAT(var, __LINE__)

#define SCOPE(end) \
for(int VAR_NAME(_i_) = 0;!VAR_NAME(_i_); end, VAR_NAME(_i_)++)

#endif
