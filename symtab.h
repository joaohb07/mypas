/***************************************************
 * Compiladores - Noturno - 2024
 * Professor Eraldo Pereira Marinho
 *
 * Mypas
 *
 * Grupo:
 * Cristian Santos de Castro
 * João Henrique Botelho
 * João Pedro Brum Terra
 *
 ***************************************************/
#include <constants.h>

enum objtype
{
    OBJ_PROCEDURE = 0,
    OBJ_FUNCTION,
    OBJ_VAR,
};

enum vartype
{
    INT32 = 0, // "int"
    INT64,     // "long"
    FLOAT32,   // "real"
    FLOAT64,   // "double"
    BOOL,      // "boolean"
    TEXT,      
    /*  TEXT está aqui apenas simbolicamente, para que os parametros do programa principal não sejam do tipo int32
        este tipo não ainda não é tratado de forma concreta no parser ou no lexer
    */
};

typedef struct _symtab_
{
    char name[MAXIDLEN];
    int objtype;
    int type;
    int lexlevel;
    int parmflag;
} SYMTAB;

extern SYMTAB symtab[];
extern int symtab_next_entry;

extern int symtab_lookup(char *, int);
extern int symtab_append(char *, int);
extern void symtab_print(void);