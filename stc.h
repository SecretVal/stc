// # Dynamic Arrays:
// Dynamic Array are expected to be a struct with the following fields:
// typedef struct {
//  void* items; // void* is only used to symbolise any type
//  size_t size;
//  size_t cap;
// } Some_Da;
// Example implemenations can be found when in STC_StringBuilder (just search here in this file).


#ifndef _STC_H_
#define _STC_H_
#include <assert.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef STC_STRIP_PREFIX
  #define shift stc_shift
  #define da_len stc_da_len
  #define da_get stc_da_get
  #define da_push stc_da_push
  #define da_push_buf stc_da_push_buf
  #define LogLevel STC_LogLevel
  #define StringBuilder STC_StringBuilder
#endif

#ifndef STC_INIT_DA_CAP
#define STC_INIT_DA_CAP 256
#endif

#define STC_SUCCESS 1
#define STC_FAILURE 1

#define stc_todo(reason) (fprintf(stderr, "TODO: %s\n", reason), exit(1))

#define stc_shift(xs, xs_sz) (assert(xs_sz > 0), xs_sz--, *xs++)
#define stc_log(log_level, fmt, ...) stc_log(log_level, fmt, ...)

#define stc_da_len(da) (sizeof(da) / sizeof(da[0]))
#define stc_da_get(da, i) (assert(i < stc_da_len(da)), da[i])
#define stc_da_push(da, item)                                             \
  do {                                                                    \
    if ((da)->count >= (da)->cap) {                                       \
      (da)->cap = (da)->cap == 0 ? STC_INIT_DA_CAP : (da)->cap * 2;       \
      (da)->items = realloc((da)->items, (da)->cap*sizeof((da)->items));  \
      assert((da)->items != NULL && "You broke or what?");                \
    }                                                                     \
                                                                          \
    (da)->items[(da)->count++] = (item);                                  \
  } while (0)                                                             \

#define stc_da_push_buf(da, buf, buf_sz)  \
  do {                                    \
    for (int i = 0; i < buf_sz; ++i) {    \
       stc_da_push(da, buf[i]);           \
    }                                     \
  } while(0)                              \

typedef struct {
  char *items;
  size_t count;
  size_t cap;
} STC_StringBuilder;

typedef enum {
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_TRACE
} STC_LogLevel;


#ifdef STC_IMPLEMTATION
void stc_log(STC_LogLevel log_level, const char *fmt, ...) {
  STC_StringBuilder sb;
}
#endif // END STC_IMPLEMTATION
#endif // END _STC_H_
