
#include "symbols.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

const char *const SYM_TEXT[SYM_COUNT] = {
    [SYM_NONE]             = "none",
    [SYM_UNKNOWN]          = "unknown",

    [SYM_DOLLAR_SIGN]      = "dollar sign",
    [SYM_EQUAL]            = "equal",
   
    [SYM_ASSIGN]           = "assignment",
    [SYM_DOT]              = "dot",

    [SYM_SLASH]            = "slash",
    [SYM_PAREN_OPEN]       = "paren open",
    [SYM_PAREN_CLOSE]      = "paren close",
    [SYM_PLUS]             = "plus",
    [SYM_MINUS]            = "minus",
    [SYM_APOSTROPHE]       = "apostrophe",
    [SYM_ASTRISK]          = "astrisk",

    [SYM_LESS_THAN]        = "less_than",
    [SYM_GREATER_THAN]     = "greater than",
    [SYM_LESS_OR_EQUAL]    = "less or equal",
    [SYM_GREATER_OR_EQUAL] = "greater or equal",
    [SYM_NOT_EQUAL]        = "not equal",

    [SYM_COLON]            = "colon",
    [SYM_SEMICOLON]        = "semicolon",
    [SYM_COMMA]            = "comma",

    [SYM_BLANK]            = "blank",

    [SYM_DECLARE]          = "declare",
    [SYM_BYTE]             = "byte",
    [SYM_ADDRESS]          = "address",
    /* [SYM_SHORT]            = "short",
     * [SYM_WORD]             = "word",
     * [SYM_DWORD]            = "dword", */
    [SYM_STRUCTURE]        = "structure",
    [SYM_BASED]            = "based",
    [SYM_AT]               = "at",
    [SYM_PUBLIC]           = "public",
    [SYM_EXTERNAL]         = "external",
    [SYM_INITIAL]          = "initial",
    [SYM_DATA]             = "data",
    [SYM_LITERALLY]        = "literally",
    [SYM_KW_PLUS]          = "kw plus",
    [SYM_KW_MINUS]         = "kw minus",
    [SYM_NOT]              = "not",
    [SYM_AND]              = "and",
    [SYM_OR]               = "or",
    [SYM_XOR]              = "xor",
    [SYM_DO]               = "do",
    [SYM_WHILE]            = "while",
    [SYM_CASE]             = "case",
    [SYM_END]              = "end",
    [SYM_TO]               = "to",
    [SYM_BY]               = "by",
    [SYM_IF]               = "if",
    [SYM_THEN]             = "then",
    [SYM_ELSE]             = "else",
    [SYM_LABEL]            = "label",
    [SYM_PROCEDURE]        = "procedure",
    [SYM_RETURN]           = "return",
    [SYM_CALL]             = "call",
    [SYM_GOTO]             = "goto",
    [SYM_REENTRANT]        = "reentrant",
    [SYM_INTERRUPT]        = "interrupt",
    [SYM_HALT]             = "halt",
    [SYM_ENABLE]           = "enable",
    [SYM_DISABLE]          = "disable",
    [SYM_KW_EOF]           = "kw eof",


    [SYM_IDENT]            = "identifier",
    [SYM_NUMBER]           = "number",
    [SYM_STRING]           = "string",
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
