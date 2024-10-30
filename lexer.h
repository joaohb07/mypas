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

enum tokens
{
    ID = 1024,
    NUM,
    ASGN,
    NUM,
    EQ,  // =
    NEQ, // !=
    LEQ, // <=
    GEQ, // >=
    LT,  // <
    GT,  // >
};

extern char lexeme[];
extern int gettoken(FILE *source);
