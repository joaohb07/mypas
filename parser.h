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

/* Ponteiro para o arquivo que contém o código-fonte do programa a ser analisado */
extern FILE *source;

/* Próximo símbolo (token) a ser processado pelo analisador sintático */
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
void expr(void);
void smpexpr(void);
int relop(void);
int isoplus(void);
int isotimes(void);
