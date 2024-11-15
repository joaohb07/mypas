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

#define MAXSTBSIZE 0x100000

SYMTAB symtab[MAXSTBSIZE];
int symtab_next_entry = 0;
// double vmem[SYMTABSIZE];
// char symtab[SYMTABSIZE][MAXIDLEN + 1];

// /*
//     lookup procura um nome na tabela de simbolos e retorna seu indice, caso não encontrar, retorna -1
// */
// int lookup(char *varname)
// {
//     int i = 0;
//     for (i = 0; i < symtab_next_entry; i++)
//     {
//         if (strcmp(varname, symtab[i]) == 0)
//             break;
//     }
//     if (i == symtab_next_entry)
//     {
//         return -1; // no achou varname em symtab
//     }
//     return i;
// }

// /*
//     store registra uma nova variavel armazenando seu nome em symtab e seu valor em vmem
// */
// void store(char *varname, double value)
// {
//     int i = lookup(varname);

//     if (i < 0)
//     {
//         i = symtab_next_entry;
//         strcpy(symtab[i], varname);
//         vmem[i] = value;
//     }
//     else
//     {
//         vmem[i] = value;
//     }
//     symtab_next_entry++;
// }

// /*
//     recall procura e retorna o valor de uma váriavel
// */
// double recall(char *varname)
// {
//     int i = lookup(varname);

//     if (i < 0)
//     {
//         return 0.0;
//     }
//     else
//     {
//         return vmem[i];
//     }
// }

// looks up a symbol append to the symbol table (symtab)
extern int symtab_lookup(char const *lexeme, int lexlevel)
{
    int i = 0;
    for (i = 0; i < symtab_next_entry; i++)
    {
        if (strcmp(lexeme, symtab[i].name) == 0 && symtab[i].lexlevel == lexlevel)
            return i;
    }
    return -1;
};
// looks up a predefined
extern int symtab_append(char const *lexeme, int lexlevel)
{
    if (symtab_lookup(lexeme, lexlevel) == -1)
    {
        SYMTAB newSymbol = {lexeme, 0, 0, lexlevel, 0};
        symtab[symtab_next_entry] = newSymbol;
        symtab_next_entry++;
        return 0;
    }
    else
    {
        return -1;
    }
};