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
#include <lexer.h>
#include <parser.h>

FILE *source;

int main(int argc, char *argv[])
{
    // if (argc == 1)
    // {
    //     fprintf(stderr, "Please provide a .pas file to compile\n");
    //     exit(1);
    // }
    // if (argc == 2)
    // {
    // source = fopen(argv[1], "r");
    source = fopen("./inputs/teste4.pas", "r");
    lookahead = gettoken(source);
    program();
    // }
    // else
    // {
    //     fprintf(stderr, "Too many arguments!\n");
    //     exit(1);
    // }
    return 0;
}