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

SYMTAB symtab[20]; // limite de 20 simbolos para testar
int symtab_next_entry = 0;

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
extern int symtab_lookup(char *lexeme, int lexlevel)
{
    int i = 0;
    for (i = 0; i < symtab_next_entry; i++)
    {
        if (strcmp(lexeme, symtab[i].name) == 0 && symtab[i].lexlevel <= lexlevel)
            return i;
    }
    return -1;
};

// looks up a predefined
extern int symtab_append(char *lexeme, int lexlevel)
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
        return 0;
    }
    else
    {
        return -1;
    }
}