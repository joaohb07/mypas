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
#include <stdio.h>
#include <stdlib.h>

extern FILE *source;
/* proximo simbolo a ser processado */
extern int lookahead;
extern void match(int expected);

void program(void);
void idlist(void);
void block(void);
void vardef(void);
void sbprgdef(void);
void beginend(void);
void stmtlst(void);
void parmlist(void);
void stmt(void);
void idstmt();
void ifstmt(void);
void whlstmt(void);
void repstmt(void);
void exprlist(void);
void term(void);
void factor(void);
void type(void);
int expr(void);
int isotimes(void);
