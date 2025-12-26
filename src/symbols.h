
#ifndef PLM_SYMBOLS_H
#define PLM_SYMBOLS_H

#include <stddef.h>

/* everything but strings are case insensitive */

/* character set:
 *   [A-Za-z0-9] 
 *   = . / ( ) + - ' * , < > : ;
 *   space tab carriage-return line-feed
 *
 * $ characters in identifiers and number are ignored.
 * any character not in this set is considered an error.
 */

typedef enum {
    SYM_NONE = 0,
    SYM_UNKNOWN = 1,

    SYM_EQUAL,          /* = */
    SYM_DOT,            /* . */
    SYM_SLASH,          /* / */
    SYM_PAREN_OPEN,     /* ( */
    SYM_PAREN_CLOSE,    /* ) */
    SYM_PLUS,           /* + */
    SYM_MINUS,          /* - */
    SYM_APOSTROPHE,     /* ' */
    SYM_MULT,           /* * */
    SYM_BRACKET_OPEN,   /* < */
    SYM_BRACKET_CLOSE,  /* > */
    SYM_COLON,          /* : */
    SYM_SEMICOLON,      /* ; */
    SYM_BLANK,          /* space, tab, carriage-return, line-feed */

    SYM_NEQ,            /* <> */
    SYM_LTE,            /* <= */
    SYM_GTE,            /* >= */
    SYM_ASSIGNMENT,     /* := */
    SYM_COMMENT,        /* same as c89 multiline style */

    SYM_IDENT,
    SYM_NUMBER,
    SYM_STRING,         /* '...' (single quotes only) */
    SYM_COUNT,
    
} symbol_t;

#define IDENT_MAX 31    /* identifiers can only be 31 characters long
                         * first char must be alpha, rest may be alphanum
                         * $ may be present in identifier, they are ignored */

/* numbers
 * ---------------------------------------------------------------------
 * number base is determined by it's suffix, [BOQDH]. 
 *   B      binary
 *   [OQ]   octal
 *   D      decimal (optional, implied by default)
 *   H      hexedecimal
 *
 * hexedecimal values must begin with a numberic value.
 * $ may be present in numbers, they are ignored
 *
 * PLM-80 specifies that numeric constants should be in the range 0-65535
 * PLM-86 maybe 32/64bit?
 */

/* strings
 * ---------------------------------------------------------------------
 *  strings use single quotes only '...'
 * to represent an apostrophe use 2 apostrophes next to each other ''.
 *
 * '''Q' represent 2 character: apostrophe and Q
 *
 * single length strings are converted to single-byte values
 * double length strings are converted to double-byte values
 *
 * PLM-86 maybe convert 3-4 character strings to values?
 */
#define STRING_MAX 255  /* max string constant len are compiler determined */

/* reserved keywords (case insensitive)
 *   DECLARE
 *   BYTE
 *   ADDRESS
 *   ? SHORT
 *   ? WORD
 *   ? DWORD
 *   STRUCTURE
 *   BASED
 *   AT
 *   PUBLIC
 *   EXTERNAL
 *   INITIAL
 *   DATA
 *
 *   LITERALLY
 *
 *   MOD
 *   NOT
 *   AND
 *   OR
 *   XOR
 *
 *   DO
 *   WHILE
 *   CASE
 *   END
 *   TO
 *   BY
 *
 *   IF
 *   THEN
 *   ELSE
 * 
 *   LABEL
 *   PROCEDURE
 *   RETURN
 *   CALL
 *   GOTO
 *   GO TO
 *   REENTRANT
 *
 *   INTERUPT   (likely unused in modern systems)
 *   HALT
 *   ENABLE
 *   DISABLE
 */

/* personal note, got to page 74 */

/* variables:
 * types (PLM-86 maybe extend to SHORT, WORD, DWORD)
 *   BYTE
 *   ADDRESS
 *
 * variables declared in a parenthesis list are guaranteed to be consecutive
 
 *     DECLARE (VAR_A, VAR_B, VAR_C) BYTE;
 *     DECLARE VAR_D ADDRESS;
 */

/* operator precenance
 *   unary '-'
 *   * / MOD
 *   + -
 *   < <= <> = >= >
 *   NOT
 *   AND
 *   OR XOR
 */


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

int sym_exists (symbols_t *self, symbols_t *syms);

#endif
/* end of file */
