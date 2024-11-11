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
#include <string.h>
#include <keywords.h>
#include <constants.h>
#include <lexer.h>

char lexeme[MAXIDLEN + 1];
int linenum = 1;

/*
  TOKENS:
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
        if ((lexeme[i] = getc(tape)) == '=')
        {
            return LEQ;
        }
        if (lexeme[i] == '>')
        {
            return NEQ;
        }
        ungetc(lexeme[i], tape);
        i--;
        ungetc(lexeme[i], tape);
        return LT;
    case '>':
        i++;
        if ((lexeme[i] = getc(tape)) == '=')
        {
            return GEQ;
        }
        ungetc(lexeme[i], tape);
        i--;
        ungetc(lexeme[i], tape);
        return GT;
    case '=':
        ungetc(lexeme[i], tape);
        return EQ;
    };
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
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
            if (i < MAXIDLEN)
                ++i;

        ungetc(lexeme[i], tape);
        lexeme[i] = 0;

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
    int i = 0;
    lexeme[i] = getc(tape);
    if (lexeme[i] == ':')
    {
        i++;
        lexeme[i] = getc(tape);
        if (lexeme[i] == '=')
        {
            lexeme[i] = 0;
            return ASGN;
        }
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;
        --i;
    }
    ungetc(lexeme[i], tape);
    lexeme[i] = 0;
    return 0;
}

/*
    NUM = [0-9]|([0-9])"."(([0-9])|"e"("+"|"-")[0-9])[0-9]|([0-9])"."(([0-9])|"e"("+"|"-")[0-9])
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

        return NUM;
    }
    ungetc(lexeme[0], tape);
    lexeme[0] = '\0';
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
            linenum++;
        if (head == EOF)
            break;
    };

    if (head == '{')
    {
        while (head != '}')
        {
            if (head == EOF)
            {
                break;
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
        return token;
    }
    if ((token = isNUM(source)))
    {
        return token;
    }
    if ((token = isASGN(source)))
    {
        return token;
    }
    if ((token = isRELOP(source)))
    {
        return token;
    }
    token = getc(source);
    return token;
}