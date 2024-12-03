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

SYMTAB symtab[MAXSTBSIZE]; // tabela de simbolos
int symtab_next_entry = 0; // proximo espaço da tabela a ser populado

/*
    symtab_lookup procura por um simbolo na tabela de simbolos
    se um simbolo da tabela tiver o mesmo nome, e um nivel lexico menor ou igual
    ao nivel do simbolo procurado, retorna o indice do simbolo na tabela, caso contrário retorna -1
*/
int symtab_lookup(char *lexeme, int lexlevel)
{
    if (lexeme == NULL || lexlevel < 1)
    {
        return -1;
    }
    for (int i = 0; i < symtab_next_entry; i++)
    {
        if ((strcmp(lexeme, symtab[i].name) == 0 && symtab[i].lexlevel <= lexlevel && symtab[i].objtype == 2) ||
            (strcmp(lexeme, symtab[i].name) == 0 && symtab[i].objtype < 2))
            return i;
    }
    return -1;
};

/*
    symtab_append registra um novo simbolo, se este ainda não foi registrado,
    um novo registro tem inicialmente apenas seu nome e nivel lexico setado.
*/
int symtab_append(char *lexeme, int lexlevel)
{
    if (lexeme == NULL || lexlevel < 1)
    {
        return -1;
    }
    if (symtab_lookup(lexeme, lexlevel) == -1)
    {
        SYMTAB new_symbol = {
            .lexlevel = lexlevel,
            .objtype = 0, //
            .parmflag = 0,
            .type = 0};

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

/*
    symtab_print imprime a tabela de simbolos
*/
void symtab_print(void)
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
