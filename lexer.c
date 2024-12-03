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
#include <string.h>
#include <constants.h>
#include <keywords.h>
#include <lexer.h>

char lexeme[MAXIDLEN + 1]; // string que armazena o simbolo lido para ser analizado
int linenum = 1;           // numero da linha
int colnum = 1;            // numero da coluna
int symbolsize;            // variavel auxiliar para a atualização de colnum

/*
  RELOP = "=" | "<>" | "<=" | ">=" | "<" | ">" | "in"
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
            symbolsize = 2;
            return LEQ;
        }
        if (lexeme[i] == '>')
        {
            symbolsize = 2;
            return NEQ;
        }
        symbolsize = 1;
        return LT;

    case '>':
        i++;
        if ((lexeme[i] = getc(tape)) == '=')
        {
            symbolsize = 2;
            return GEQ;
        }
        symbolsize = 1;
        return GT;

    case '=':
        symbolsize = 1;
        return EQ;
    case 'i':
        i++;
        if ((lexeme[i] = getc(tape)) == 'n')
        {
            symbolsize = 2;
            return IN;
        }
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

        if (i > MAXIDLEN) // verifica se o identificador não excede o tamanho limite
        {
            lexeme[i] = 0;
            fprintf(stderr, IDENTIFIER_NAME_ERROR, lexeme, linenum, colnum);
            return 0;
        }
        ungetc(lexeme[i], tape);
        lexeme[i] = 0;

        symbolsize = i;

        int token = iskeyword(lexeme); // verifica se o identificador encontrado não é palavra reservada
        if (token)                     // se for palavra reservada, retorna o token desta palavra,
            return token;
        else // caso contrário retorna o token ID
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
    skipspaces ignora os espaços em branco, atualiza os valores de linenum e colnum
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
    gettoken consome um simbolo de source e o classifica, se for possivel
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
