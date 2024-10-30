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

int lookup(char *varname);
void store(char *varname, double value);
double recall(char *varname);

/* memória da calculadora */
extern double vmem[];
/* tabela de simbolos */
extern char symtab[SYMTABSIZE][MAXIDLEN + 1];
/* proximo item da tabela */
extern int symtab_next_entry;
