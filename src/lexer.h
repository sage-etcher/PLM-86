
#ifndef PLM86_LEXER_H
#define PLM86_LEXER_H

#include "symbols.h"

#include <stdint.h>
#include <stdio.h>

#ifndef scanner_t
/* test environment */

typedef struct {
    const char *filename;
    FILE *fp;
    char c;

    uint64_t number;
    char ident[IDENT_MAX+1];
    char str[STRING_MAX+1];
} scanner_t;

int scanner_init (scanner_t *self, const char *filename);
void scanner_free (scanner_t *self);
symbols_t scanner_scan (scanner_t *self);

#endif /* !defined scanner_t */

typedef struct {
    scanner_t scanner;
    symbols_t syms;
} lexer_t;

int lexer_parse (lexer_t *self, const char *filename);


#endif
/* end of file */
