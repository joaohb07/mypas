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
#include <stdlib.h>
#include <constants.h>
#include <keywords.h>
#include <symtab.h>
#include <lexer.h>
#include <parser.h>

// Variáveis globais para controle do analisador
int lexlevel = 1;      // Nível léxico atual
int error_count = 0;   // Contador de erros
int current_type = 0;  // Tipo atual de variável ou expressão
int current_index = 0; // Índice atual na tabela de símbolos
int lookahead;         // Próximo token a ser analisado

/*
 * Função principal do programa.
 * Verifica a estrutura geral começando com "PROGRAM",
 * processa o identificador, a lista de parâmetros e o bloco principal.
 */
void program(void)
{
    match(PROGRAM);
    match(ID);
    match('(');
    current_index = symtab_next_entry;
    idlist(); // Processa a lista de identificadores
    for (int i = current_index; i < symtab_next_entry; i++)
    {
        symtab[i].objtype = OBJ_VAR; // Marca como variável
        symtab[i].parmflag = 1;      // Indica que é um parâmetro
        symtab[i].type = TEXT;       // Define o tipo como texto
    }
    match(')');
    match(';');
    block(); // Analisa o bloco principal
    match('.');
}

/*
 * Processa uma lista de identificadores, verificando duplicatas.
 */
void idlist(void)
{
    int error_stat = 0;
_idlist:
    error_stat = symtab_append(lexeme, lexlevel);
    if (error_stat)
    {
        fprintf(stderr, SYMBOL_ALREADY_DEFINED_ERROR, lexeme, linenum, colnum);
        error_count++;
    }

    match(ID);
    if (lookahead == ',') // Verifica separador de lista
    {
        match(',');
        goto _idlist; // Repete para o próximo identificador
    }
}

/*
 * Analisa o bloco principal de declarações e comandos.
 */
void block(void)
{
    vardef();   // Definições de variáveis
    sbprgdef(); // Subprogramas (procedures e functions)
    beginend(); // Corpo principal do programa ou do subprograma
}

/*
 * Analisa e armazena declarações de variáveis na tabela de símbolos.
 */
void vardef(void)
{
    if (lookahead == VAR)
    {
        match(VAR);
    _idlist:
        current_index = symtab_next_entry;
        idlist();
        match(':');
        type(); // Identifica o tipo da variável
        match(';');
        for (int i = current_index; i < symtab_next_entry; i++)
        {
            symtab[i].objtype = OBJ_VAR;   // Marca como variável
            symtab[i].parmflag = 0;        // Não é parâmetro
            symtab[i].type = current_type; // Atribui o tipo atual
        }
        if (lookahead == ID)
            goto _idlist; // Continua com a próxima declaração
    }
}

/*
 * Analisa subprogramas (procedures e functions).
 */
void sbprgdef(void)
{
    int error_stat = 0;
    while (lookahead == PROCEDURE || lookahead == FUNCTION)
    {
        int isfunc = (lookahead == FUNCTION);
        match(lookahead);
        int first_func_pro_index = symtab_next_entry;
        error_stat = symtab_append(lexeme, lexlevel);
        if (error_stat)
        {
            fprintf(stderr, SYMBOL_ALREADY_DEFINED_ERROR, lexeme, linenum, colnum);
            error_count++;
        }

        match(ID);
        parmlist(); // Processa a lista de parâmetros
        if (isfunc)
        {
            match(':');
            type(); // Tipo de retorno da função
            symtab[first_func_pro_index].type = current_type;
            symtab[first_func_pro_index].objtype = OBJ_FUNCTION;
        }
        match(';');
        lexlevel++; // Aumenta o nível léxico para o bloco interno
        block();
        match(';');

        puts("symtab após bloco:");
        symtab_print();

        symtab_next_entry = first_func_pro_index + 1;
        lexlevel--; // Retorna ao nível léxico anterior
    };
}

/*
 * Analisa um bloco entre "BEGIN" e "END".
 */
void beginend(void)
{
    match(BEGIN);
    stmtlst(); // Lista de comandos
    match(END);
}

/*
 * Analisa uma lista de comandos separados por ponto e vírgula.
 */
void stmtlst(void)
{
_stmtlst:
    stmt(); // Analisa um comando
    if (lookahead == ';')
    {
        match(';');
        goto _stmtlst; // Continua para o próximo comando
    }
}

/*
 * Verifica e analisa o tipo atual.
 */
void type(void)
{
    switch (lookahead)
    {
    case INTEGER:
        current_type = INT32; // Define o tipo como inteiro (32 bits)
        match(lookahead);
        break;
    case LONG:
        current_type = INT64; // Inteiro longo (64 bits)
        match(lookahead);
        break;
    case REAL:
        current_type = FLOAT32; // Ponto flutuante (32 bits)
        match(lookahead);
        break;
    case DOUBLE:
        current_type = FLOAT64; // Ponto flutuante (64 bits)
        match(lookahead);
        break;
    default:
        current_type = BOOL; // Booleano
        match(BOOLEAN);
    }
}

/*
 * Verifica se o próximo token é o esperado.
 * Caso contrário, emite um erro de sintaxe.
 */
void match(int expected)
{
    if (lookahead == expected)
        lookahead = gettoken(source); // Lê o próximo token
    else
    {
        fprintf(stderr, SYNTAX_ERROR, lexeme, linenum, colnum);
        exit(-3);
    }
}
