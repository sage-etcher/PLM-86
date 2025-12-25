
#include "symbols.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

const char *const SYM_TEXT[SYM_COUNT] = {
    [SYM_UNKNOWN] = "unknown symbol",
    [SYM_IDENT]   = "identifier",
    [SYM_NUMBER]  = "number",
};


int
sym_add (symbols_t *self, symbol_t sym)
{
    size_t i = 0;

    assert (self != NULL);
    assert (self->n < SYMS_MAX_N);
    assert (sym < SYM_COUNT);

    /* check if symbol already in buffer */
    for (i = 0; i < self->n; i++)
    {
        if (self->syms[i] == sym) 
        {
            return 2;
        }
    }

    /* otherwise add the value to the end of the list */
    self->syms[self->n++] = sym;
    return 0;
}

int
sym_remove (symbols_t *self, symbol_t sym)
{
    size_t i = 0;

    assert (self != NULL);
    assert (self->n < SYMS_MAX_N);
    assert (sym < SYM_COUNT);

    /* find symbol in buffer */
    for (i = 0; i < self->n; i++)
    {
        if (self->syms[i] == sym)
        {
            /* remove the symbol if it is found */
            memmove (&self->syms[i], &self->syms[i], --self->n - i);
            return 0;
        }
    }

    /* then element was not found */
    return 1;
}

int
sym_exists (symbols_t *haystack, symbols_t *needle)
{
    size_t ii = 0;
    size_t jj = 0;

    for (ii = 0; ii < haystack->n; ii++)
    {
        for (jj = 0; jj < needle->n; jj++)
        {
            if (haystack->syms[ii] == needle->syms[jj])
            {
                return needle->syms[jj];
            }
        }
    }

    return 0;
}


/* end of file */
