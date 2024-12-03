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
#include <symtab.h>
#include <stdio.h>

#define MAXSTBSIZE 0x100000

SYMTAB symtab[MAXSTBSIZE];
int symtab_next_entry = 0;

/*
Realiza uma busca na tabela de simbolos
*/
int symtab_lookup(char *lexeme, int lexlevel)
{
    int i = 0;
    for (i = 0; i < symtab_next_entry; i++)
    {
        // Verifica se o simbolo lido consta na tabela de simbolo
        /*
        A verificação se dá primariamente pelo nome do simbolo, no caso de variaveis, o valor do nivel lexico na tabela tem de ser menor ou igual ao simbolo lido
        para que variaveis de lexlevel L sejam acessiveis em L+1
        */
        // E verifica-se tambem se o simbolo lido é uma variavel (ter o .objtype == 2) ou não (ter o .objtype < 2)
        if ((strcmp(lexeme, symtab[i].name) == 0 && symtab[i].lexlevel <= lexlevel && symtab[i].objtype == 2) ||
            (strcmp(lexeme, symtab[i].name) == 0 && symtab[i].objtype < 2))
            return i;
    }
    return -1;
};

/*
Registra um novo simbolo na tabela de simbolos
*/
int symtab_append(char *lexeme, int lexlevel)
{
    if (symtab_lookup(lexeme, lexlevel) == -1)
    {
        SYMTAB new_symbol = {
            .lexlevel = lexlevel,
            .objtype = 0,
            .parmflag = 0,
            .type = 0};

        if (lexeme == NULL)
        {
            return -1;
        }

        strcpy(new_symbol.name, lexeme);

        symtab[symtab_next_entry] = new_symbol;
        symtab_next_entry++;
        return 0;
    }
    else
    {
        return -1;
    }
}

// print symtab for tests purpouses
void symtab_print()
{
    int i = 0;
    char objtype[MAXIDLEN];
    char type[MAXIDLEN];
    char isparam[4];

    printf("#  | %-33s | LEXLEVEL | OBJECT TYPE |   TYPE   | IS PARAM? \n", "NAME");
    puts("-------------------------------------------------------------------------------------");
    for (i = 0; i < symtab_next_entry; i++)
    {
        switch (symtab[i].objtype)
        {
        case 0:
            strcpy(objtype, "procedure");
            break;
        case 1:
            strcpy(objtype, "function");
            break;
        default:
            strcpy(objtype, "variable");
        }
        switch (symtab[i].type)
        {
        case 0:
            strcpy(type, "int32");
            break;
        case 1:
            strcpy(type, "int64");
            break;
        case 2:
            strcpy(type, "float32");
            break;
        case 3:
            strcpy(type, "float64");
            break;
        case 4:
            strcpy(type, "boolean");
            break;
        default:
            strcpy(type, "text");
        }
        if (symtab[i].parmflag == 0)
        {
            strcpy(isparam, "no");
        }
        else
        {
            strcpy(isparam, "yes");
        }
        printf("%-3d| %-33s | %-8d | %-11s | %-8s | %s \n",
               i, symtab[i].name, symtab[i].lexlevel, objtype, type, isparam);
    }
    puts("");
}
