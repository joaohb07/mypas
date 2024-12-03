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
#include <constants.h>
#include <keywords.h>
#include <symtab.h>
#include <lexer.h>
#include <parser.h>

int lexlevel = 1;
int current_type = 0;  // tipo dos ultimos simbolos processados
int current_index = 0; // indice auxiliar para atribuição de propriedades dos simbolos
int lookahead;         // proximo simbolo a ser processado

/*
    program analisa a estrutura completa de um código pascal
*/
void program(void)
{
    match(PROGRAM);
    match(ID);
    match('(');
    current_index = symtab_next_entry;

    idlist();
    // atribuindo propriedades dos simbolos registrados:
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
    idlist analisa uma lista de identificadores separados por virgula,
    registrando na tabela de simbolos o nome e o nivel lexico de cada.
*/
void idlist(void)
{
    int error_stat = 0;
_idlist:
    error_stat = symtab_append(lexeme, lexlevel);
    if (error_stat)
        fprintf(stderr, SYMBOL_ALREADY_DEFINED_ERROR, lexeme, linenum, colnum);

    match(ID);
    if (lookahead == ',') // Verifica separador de lista
    {
        match(',');
        goto _idlist; // Repete para o próximo identificador
    }
}

/*
    block analisa um bloco que:
    - pode conter definição de variaveis
    - pode conter definição de subprogramas e seus blocos
    - deve conter "begin", uma lista de statments  e "end"
*/
void block(void)
{
    vardef();   // definições de variáveis
    sbprgdef(); // subprogramas (procedures e functions)
    beginend(); // corpo principal do programa ou do subprograma
}

/*
    vardef analisa declarações de variáveis e às na tabela de símbolos.
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
        type(); // utiliza variavel global para guardar o tipo da variavel lida

        match(';');
        // atribuindo propriedades dos simbolos registrados:
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
    sbprgdef analisa subprogramas (procedures e functions), juntamente com seus respectivos blocos
    ao final de cada bloco, os simbolos registrados com nivel lexico L+1 são sobreescritos
*/
void sbprgdef(void)
{
    int error_stat = 0;
    while (lookahead == PROCEDURE || lookahead == FUNCTION)
    {
        int isfunc = (lookahead == FUNCTION);
        match(lookahead);
        //  aqui é necessário salvar o valor atual de symtab_next_entry em uma variavel local
        //  pois current_index é alterado em block();
        int parmlist_index = symtab_next_entry;

        error_stat = symtab_append(lexeme, lexlevel);
        if (error_stat)
            fprintf(stderr, SYMBOL_ALREADY_DEFINED_ERROR, lexeme, linenum, colnum);

        match(ID);
        parmlist(); // analisa a lista de parâmetros

        // em symtab_append o objtype default é 0 (procedure)
        // portanto este valor só é alterado aqui o simbolo for uma função
        if (isfunc)
        {
            match(':');
            type();
            symtab[parmlist_index].type = current_type;
            symtab[parmlist_index].objtype = OBJ_FUNCTION;
        }
        match(';');
        lexlevel++; // sobe o lexical level ao entrar em um bloco
        block();
        printf("symtab antes de sair de um bloco de nivel lexico %d:\t(linha %d no arquivo .pas)\n", lexlevel, linenum);
        symtab_print();
        match(';');
        symtab_next_entry = parmlist_index + 1;
        lexlevel--; // desce o lexical level ao sair de um bloco
    };
}

/*
    beginend analisa um bloco e suas estruturas entre "BEGIN" e "END".
*/
void beginend(void)
{
    match(BEGIN);
    stmtlst(); // Lista de comandos
    match(END);
}

/*
    stmtlst analisa uma lista de instruções separados por ponto e vírgula.
*/
void stmtlst(void)
{
_stmtlst:
    stmt(); // Analisa um comando
    if (lookahead == ';')
    {
        match(';');
        goto _stmtlst;
    }
}

/*
    parmlist analisa uma lista de parâmetros de uma função ou procedimento
*/
void parmlist(void)
{
    if (lookahead == '(')
    {
        match('(');
    _parmlist:
        if (lookahead == VAR)
        {
            match(VAR);
        }
        // parametros de uma função ou procedure definida no nivel lexico L
        // terão nivel lexico L+1
        lexlevel++;
        current_index = symtab_next_entry;
        idlist();
        lexlevel--;
        match(':');
        type();
        // atribuindo propriedades dos simbolos registrados:
        for (int i = current_index; i < symtab_next_entry; i++)
        {
            symtab[i].objtype = OBJ_VAR;
            symtab[i].parmflag = 1;
            symtab[i].type = current_type;
        }
        if (lookahead == ';')
        {
            match(';');
            goto _parmlist;
        }
        match(')');
    }
}

/*
    stmt analisa uma instrução (stmt), que pode ser:
    - begin
    - idstmt  (atribuição)
    - ifstmt  (condicional)
    - whlstmt (while)
    - repstmt (repeat)
    - expr;
*/
void stmt(void)
{
    switch (lookahead)
    {
    case BEGIN:
        beginend();
        break;
    case ID:
        idstmt();
        break;
    case IF:
        ifstmt();
        break;
    case WHILE:
        whlstmt();
        break;
    case REPEAT:
        repstmt();
        break;
    default:;
    }
}

/*
    idistmt analisa uma instrução que começa com um identificador, que pode ser:
    - Uma atribuição
    - Uma chamada de função ou procedimento com uma lista de expressões

    idistmt também verifica se o identificador está declarado na tabela de símbolos.
*/
void idstmt(void)
{
    int id_position = symtab_lookup(lexeme, lexlevel);
    if (id_position < 0)
    {
        fprintf(stderr, SYMBOL_NOT_FOUND_ERROR, lexeme, linenum, colnum);
    }
    match(ID);
    if (lookahead == ASGN)
    {
        match(ASGN);
        expr();
    }
    else
    {
        exprlist();
    }
}

/*
    ifstmt analisa uma instrução condicional if-then[-else]
*/
void ifstmt(void)
{
    match(IF);
    expr();
    match(THEN);
    stmt();
    if (lookahead == ELSE)
    {
        match(ELSE);
        stmt();
    }
}

/*
    whlstmt analisa um laço de repetição da forma:
    while (expressão é verdadeira) do
        (instruções)
*/
void whlstmt(void)
{
    match(WHILE);
    expr();
    match(DO);
    stmt();
}

/*
    repstmt analisa um laço de repetição da forma:
    repeat
        (instruções)
    until
        (expressão ser verdadeira)
*/
void repstmt(void)
{
    match(REPEAT);
    stmtlst();
    match(UNTIL);
    expr();
}

/*
    exprlist analisa uma ou mais expressões entre parenteses separadas por virgula
*/
void exprlist(void)
{
    if (lookahead == '(')
    {
        match('(');
    _exprlist:
        expr();
        if (lookahead == ',')
        {
            match(',');
            goto _exprlist;
        }
        match(')');
    }
}

/*
    term analisa um ou mais fatores "separados" por * ou /
*/
void term(void)
{
    factor();
    while (isotimes())
    {
        match(lookahead);
        factor();
    }
}

/*
    factor analisa um fator que pode ser:
    - identificador
    - numero
    - expressãos entre parenteses
*/
void factor(void)
{
    switch (lookahead)
    {
    case ID:
        match(ID);
        if (lookahead == ASGN)
        {
            match(ASGN);
            expr();
        }
        else if (lookahead == '(')
        {
            exprlist();
        }
        break;
    case NUM:
        match(NUM);
        break;
    default:
        match('(');
        expr();
        match(')');
        break;
    }
}

/*
    expr analisa uma expressão, que pode ser:
    - Uma expressão simples
    - Uma expressão relacional (smpexpr relop smpexpr)
*/
void expr(void)
{
    smpexpr();
    if (relop())
    {
        match(lookahead);
        smpexpr();
    }
}

/*
    relop verifica se o lookahead é um operador relacional.
*/
int relop(void)
{
    switch (lookahead)
    {
    case LT:  // <
    case LEQ: // <=
    case EQ:  // =
    case NEQ: // <>
    case GEQ: // >=
    case GT:  // >
    case IN:  // IN
        return lookahead;
    default:
        return 0;
    }
}

/*
    smpexpr analisa uma expressão simples, que é composta por termos conectados
    por operadores '+' ou '-'.
     também pode começar com um operador unário.
*/
void smpexpr(void)
{
    if (lookahead == '+' || lookahead == '-')
    {
        match(lookahead);
    }
    term();
    while (isoplus())
    {
        match(lookahead);
        term();
    }
}

/*
    isotimes verifica se o lookahead é um operador multiplicativo ('*' ou '/').
*/
int isotimes(void)
{
    switch (lookahead)
    {
    case '*':
    case '/':
        return lookahead;
    default:
        return 0;
    }
}

/*
    isoplus verifica se o lookahead é um operador aditivo ('+' ou '-').
*/
int isoplus(void)
{
    switch (lookahead)
    {
    case '+':
    case '-':
        return lookahead;
    default:
        return 0;
    }
}

/*
    type analisa e define o tipo atual, baseado no lookahead.
    E atualiza a variável global 'current_type'.
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
   match compara o valor de lookahead com um valor esperado
*/
void match(int expected)
{
    if (lookahead == expected)
    {
        lookahead = gettoken(source);
    }
    else
    {
        fprintf(stderr, SYNTAX_ERROR, lexeme, linenum, colnum);
        exit(-3);
    }
}
