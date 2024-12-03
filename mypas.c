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
#include <string.h>
#include <symtab.h>
#include <lexer.h>
#include <constants.h>
#include <parser.h>

FILE *source;

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "%s", FILE_ERROR);
        exit(1);
    }
    if (argc == 2)
    {
        source = fopen(argv[1], "r");
        char *extension = strrchr(argv[1], '.');

        if (extension && strcmp(extension, ".pas") == 0)
        {
            lookahead = gettoken(source);
            program();

            puts("symtab final:");
            symtab_print();
        }
        else
        {
            fprintf(stderr, "%s", FILE_ERROR);
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "%s", TOO_MANY_ARGS_ERROR);
        exit(1);
    }
    return 0;
}