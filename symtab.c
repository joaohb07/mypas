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

// #define MAXSTBSIZE 0x100000
#define MAXSTBSIZE 20

SYMTAB symtab[MAXSTBSIZE]; // limite de 20 simbolos para testar
int symtab_next_entry = 0;


// looks up a symbol append to the symbol table (symtab)
int symtab_lookup(char *lexeme, int lexlevel)
{
    int i = 0;
    for (i = 0; i < symtab_next_entry; i++)
    {
        if ((strcmp(lexeme, symtab[i].name) == 0 && symtab[i].lexlevel == lexlevel) || (strcmp(lexeme, symtab[i].name) == 0 && symtab[i].objtype == 1))
            return i;
    }
    return -1;
};

// looks up a predefined
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
void symtab_print(){
    int i = 0;
    for (i = 0; i < symtab_next_entry; i++)
    {
        printf("Index: %d\n",i);
        printf("%s\n", symtab[i].name);
        printf("lexical level: %d\n", symtab[i].lexlevel);
        switch (symtab[i].objtype){
            case 0:
                printf("Procedure\n");
                break;
            case 1:
                printf("Function\n");
                break;
            default:
                printf("Variable\n");
        }
        switch (symtab[i].type){
            case 0:
                printf("int32\n");
                break;
            case 1:
                printf("int64\n");
                break;
            case 2:
                printf("float32\n");
                break;
            case 3:
                printf("float64\n");
                break;    
            default:
                printf("boolean\n");
        }
        if (symtab[i].parmflag == 0) {
            printf("Variable\n");
        } else {
            printf("Parameter\n");
        }
        printf("\n");
    }
};