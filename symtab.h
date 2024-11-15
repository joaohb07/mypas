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

// int lookup(char *varname);
// void store(char *varname, double value);
// double recall(char *varname);
// /* memória da calculadora */
// extern double vmem[];
// /* tabela de simbolos */
// extern char symtab[SYMTABSIZE][MAXIDLEN + 1];
// /* proximo item da tabela */
// extern int symtab_next_entry;

typedef struct _symtab_
{
    char *name[MAXIDLEN];
    int objtype; // objtype pode ser == 0 if procedure; == 1 if function; == 2 if variable
    int type;    // type == 0 if int; type == 1 if int64; == 2 if float32; == 3 if float64; == 4 if bool
    int lexlevel;
    int parmflag; // == 0 if variable; == 1 if parameter
} SYMTAB;

extern SYMTAB symtab[];
// looks up a symbol append to the symbol table (symtab)
extern int symtab_lookup(char const *, int);
// looks up a predefined
extern int symtab_append(char const *, int);
