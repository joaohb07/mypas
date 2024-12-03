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
#include <constants.h>

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
    "integer",
    "long",
    "boolean",
    "double",
    "real",
    "end"};

/*
Verifica se o identificador lido é uma palavra chave
*/
int iskeyword(char *lexeme)
{
    int token;
    char identifier[MAXIDLEN];
    strcpy(identifier, lexeme);

    for (int i = 0; i < strlen(identifier); ++i)
    {
        identifier[i] = tolower(identifier[i]); // Converte valor para lowercase para realizar a comparação
    }

    for (token = BEGIN; token <= END; token++)
    {
        if (strcmp(identifier, keyword[token - BEGIN]) == 0)
            return token;
    }
    return 0;
}