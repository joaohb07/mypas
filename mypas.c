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
    // if (argc < 1)
    // {
    //     printf("Please provide a .pas file to compile");
    //     exit(1);
    // }
    // else
    // {
    source = fopen("input.pas", "r+");
    lookahead = gettoken(source);
    program();
    // }

    return 0;
}