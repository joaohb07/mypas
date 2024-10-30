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
#include <keywords.h>
#include <string.h>

char *keyword[] = {
    "begin",
    "program",
    "if",
    "then",
    "else",
    "procedure",
    "function",
    "while",
    "do",
    "repeat",
    "until",
    "var",
    "in",
    "end"};

int iskeyword(char *identifier)
{
    int token;
    for (token = BEGIN; token <= END; token++)
    {
        if (strcmp(identifier, keyword[token - BEGIN]))
            return token;
    }
    return 0;
}