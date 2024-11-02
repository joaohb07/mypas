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
#include <string.h>
#include <ctype.h>
#include <keywords.h>

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

    for (int i = 0; i < strlen(identifier); ++i)
    {
        identifier[i] = tolower(identifier[i]);
    }

    for (token = BEGIN; token <= END; token++)
    {
        if (strcmp(identifier, keyword[token - BEGIN]) == 0)
            return token;
    }
    return 0;
}