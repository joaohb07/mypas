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
#include <ctype.h>
#include <stdlib.h>
#include <constants.h>
#include <string.h>
#include <keywords.h>
#include <lexer.h>

char lexeme[MAXIDLEN + 1];
int linenum = 1;
int colnum = 1;
int symbolsize;

/*
    Operadores relacionais:
    EQ,  // =
    NEQ, // <>
    LEQ, // <=
    GEQ, // >=
    LT,  // <
    GT  // >
*/
int isRELOP(FILE *tape)
{
    int i = 0;
    switch (lexeme[i] = getc(tape))
    {
    case '<':
        i++;
        lexeme[i] = getc(tape);
        if (lexeme[i] == '=')
        {
            return LEQ;
        }
        if (lexeme[i] == '>')
        {
            return NEQ;
        }
        return LT;

    case '>':
        i++;
        if ((lexeme[i] = getc(tape)) == '=')
        {
            return GEQ;
        }
        return GT;

    case '=':
        return EQ;
    };
    ungetc(lexeme[i], tape);
    lexeme[0] = 0;
    return 0;
}

/*
    ID = [A-Za-z][A-Za-z0-9]*
*/
int isID(FILE *tape)
{
    int i = 0;

    if (isalpha(lexeme[i] = getc(tape)))
    {
        ++i;
        while (isalnum(lexeme[i] = getc(tape)))
            ++i;

        if (i > MAXIDLEN)
        {
            lexeme[i] = 0;
            fprintf(stderr, IDENTIFIER_NAME_ERROR, lexeme, linenum, colnum);
            return 0;
        }

        ungetc(lexeme[i], tape);
        lexeme[i] = 0;

        symbolsize = i;

        int token = iskeyword(lexeme);
        if (token)
            return token;
        else
            return ID;
    }
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
    return 0;
}

/*
    ASGN = ":="
*/
int isASGN(FILE *tape)
{

    if ((lexeme[0] = getc(tape)) == ':')
    {
        if ((lexeme[1] = getc(tape)) == '=')
        {
            symbolsize = 2;
            lexeme[2] = 0;
            return ASGN;
        }
        ungetc(lexeme[1], tape);
    }
    ungetc(lexeme[0], tape);
    lexeme[0] = 0;
    return 0;
}

/*
    isNUM valida números de ponto flutuante que são lidos pelo fscanf
*/
int isNUM(FILE *tape)
{
    lexeme[0] = getc(tape);

    if (isdigit(lexeme[0]))
    {
        ungetc(lexeme[0], tape);

        float lexval;

        fscanf(tape, "%f", &lexval);

        sprintf(lexeme, "%f", lexval);

        symbolsize = snprintf(lexeme, sizeof(lexeme), "%g", lexval);

        return NUM;
    }
    ungetc(lexeme[0], tape);
    lexeme[0] = 0;
    return 0;
}

/*
    skipspaces ignora os espaços em branco e troca fim de linha por ; para delimitar expressões
*/
void skipspaces(FILE *tape)
{
    int head;

_skipspaces:
    while (isspace(head = getc(tape)))
    {
        if (head == '\n')
        {
            colnum = 1;
            linenum++;
        }
        if (head == EOF)
        {
            break;
        }
        if (head == '\t')
        {
            colnum += 4;
        }
        else
        {
            colnum++;
        }
    };

    if (head == '{')
    {
        int comment_begin_line = linenum;
        while (head != '}')
        {
            if (head == EOF)
            {
                fprintf(stderr, UNTERMINED_COMMENT_ERROR, comment_begin_line);
                exit(1);
            }
            if (head == '\n')
                linenum++;
            head = getc(tape);
        }
        goto _skipspaces;
    }

    ungetc(head, tape);
}

/*
    gettoken verifica se o tipo do proximo simbolo a ser processado
*/
int gettoken(FILE *source)
{
    int token;
    skipspaces(source);

    if ((token = isID(source)))
    {
        colnum += symbolsize;
        return token;
    }
    if ((token = isNUM(source)))
    {
        colnum += symbolsize;
        return token;
    }
    if ((token = isASGN(source)))
    {
        colnum += symbolsize;
        return token;
    }
    if ((token = isRELOP(source)))
    {
        colnum += symbolsize;
        return token;
    }
    token = getc(source);
    colnum++;
    return token;
}
