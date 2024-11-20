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
#pragma once
#include <constants.h>

typedef struct _symtab_
{
    char name[MAXIDLEN];
    int objtype; 
// objtype pode ser == 0 if procedure; 
//== 1 if function; 
//== 2 if variable
    int type;    
// type == 0 if int;
// type == 1 if int64;
// == 2 if float32;
// == 3 if float64;
// == 4 if bool
    int lexlevel;
    int parmflag;
// == 0 if variable;
// == 1 if parameter
} SYMTAB;

extern SYMTAB symtab[];
// looks up a symbol append to the symbol table (symtab)
extern int symtab_lookup(char *, int);
// looks up a predefined
extern int symtab_append(char *, int);

extern void symtab_print();

extern int symtab_next_entry;
