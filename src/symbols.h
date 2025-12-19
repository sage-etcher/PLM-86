
#ifndef PLM_SYMBOLS_H
#define PLM_SYMBOLS_H

#include <stddef.h>

typedef enum {
    SYM_UNKNOWN,
    SYM_IDENT,
    SYM_NUMBER,
    SYM_COUNT,
} symbol_t;

#define SYMS_MAX_N 5

typedef struct {
    symbol_t syms[SYMS_MAX_N];
    size_t n;
} symbols_t;

#define NEW_SYMS1(x)   ((symbols_t){ .n = 1, .syms = { (x)      } })
#define NEW_SYMS2(x,y) ((symbols_t){ .n = 2, .syms = { (x), (y) } })

extern const char *const SYM_TEXT[SYM_COUNT];

int sym_add (symbols_t *self, symbol_t sym);
int sym_remove (symbols_t *self, symbol_t sym);

#endif
/* end of file */
