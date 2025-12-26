
#include "lexer.h"

#include "symbols.h"

#include <stdlib.h>


static int accept (lexer_t *self, symbols_t syms);
static void expect (lexer_t *self, symbols_t syms);

static int
accept (lexer_t *self, symbols_t syms)
{
    if (sym_exists (&self->syms, &syms))
    {
        self->syms = scanner_scan (&self->scanner);
    }
    return 0;
}

static void
expect (lexer_t *self, symbols_t syms)
{
    if (!accept (self, syms))
    {
        fprintf (stderr, "syntax error\n");
        exit (EXIT_FAILURE);
    }
}


static int
parse_restricted_expression (lexer_t *self)
{
    /* restricted reference */
    if (accept (self, SYMS_1 (SYM_DOT)))
    {
        expect (self, SYMS_1 (SYM_IDENT));

        /* restrited subscript */
        if (accept (self, SYMS_1 (SYM_PAREN_OPEN)))
        {
            /* restricted reference */
            while (accept (self, SYMS_1 (SYM_MINUS))) {}
            expect (self, SYMS_1 (SYM_NUMBER));
        }
    }
    return 0;
}

static int
parse_declare (lexer_t *self)
{
    if (!accept (self, SYMS_1 (SYM_DECLARE)))
    {
        return 0;
    }

    /* declare elelement list */
    do {
        /* unfactored/factored elelement */

        /* variable element */
        if (accept (self, SYMS_1 (SYM_IDENT)))
        {
            /* based name */
            if (accept (self, SYMS_1 (SYM_BASED)))
            {
                /* base specifier */
                expect (self, SYMS_1 (SYM_IDENT));

                if (accept (self, SYMS_1 (SYM_DOT)))
                {
                    expect (self, SYMS_1 (SYM_IDENT));
                }
            }

            /* dimention specifier */
            if (accept (self, SYMS_1 (SYM_PAREN_OPEN)))
            {
                expect (self, SYMS_2 (SYM_NUMBER, SYM_ASTRISK));
                expect (self, SYMS_1 (SYM_PAREN_CLOSE));
            }

            /* variable type */
            expect (self, SYMS_2 (SYM_BYTE, SYM_ADDRESS));

            /* variable attributes */
            if (!accept (self, SYMS_1 (SYM_EXTERNAL)))
            {
                (void)accept (self, SYMS_1 (SYM_PUBLIC));

                if (accept (self, SYMS_1 (SYM_AT)))
                {
                    expect (self, SYMS_1 (SYM_PAREN_OPEN));
                    (void)parse_restricted_expression (self);
                    expect (self, SYMS_1 (SYM_PAREN_CLOSE));
                }
            }
            
            /* initializations */
            if (accept (self, SYMS_2 (SYM_INITIAL, SYM_DATA)))
            {
                expect (self, SYMS_1 (SYM_PAREN_OPEN));
                do {
                    if (!parse_restricted_expression (self))
                    {
                        expect (self, SYMS_1 (SYM_STRING));
                    }
                } while (accept (self, SYMS_1 (SYM_COMMA)));
                expect (self, SYMS_1 (SYM_PAREN_CLOSE));
            }



        }



    } while (accept (self, SYMS_1 (SYM_COMMA)));

    expect (self, SYMS_1 (SYM_SEMICOLON));

    return 1;
}

int
lexer_parse (lexer_t *self, const char *filename)
{
    scanner_init (&self->scanner, filename);

    self->syms = scanner_scan (&self->scanner);
    


    scanner_free (&self->scanner);
    return 0;
}


/* end of file */
