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
#include <keywords.h>
#include <symtab.h>
#include <lexer.h>
#include <parser.h>

int lexlevel = 1;
int error_count = 0;
int current_type = 0;
int current_index = 0;

int lookahead;

void program(void)
{

    match(PROGRAM);
    match(ID);
    match('(');
    current_index = symtab_next_entry;
    idlist();
    for (int i = current_index; i < symtab_next_entry; i++)
    {
        symtab[i].objtype = 2; // VAR_TYPE
        symtab[i].parmflag = 1;
    }
    match(')');
    match(';');
    block();
    match('.');
}

void idlist(void)
{
    int error_stat = 0;
_idlist:
    error_stat = symtab_append(lexeme, lexlevel);
    if (error_stat)
    {
        fprintf(stderr, "FATAL ERROR: symbol \"%s\" already defined\n", lexeme);
        error_count++;
    }

    match(ID);
    if (lookahead == ',')
    {
        match(',');
        goto _idlist;
    }
}

void block(void)
{
    vardef();
    sbprgdef();
    beginend();    
}

void vardef(void)
{
    if (lookahead == VAR)
    {
        match(VAR);
    _idlist:
        current_index = symtab_next_entry;
        idlist();
        match(':');
        type();
        match(';');
        for (int i = current_index; i < symtab_next_entry; i++)
        {
            symtab[i].objtype = 2; // VAR_TYPE
            symtab[i].parmflag = 0;
            symtab[i].type = current_type;
        }
        if (lookahead == ID)
            goto _idlist;
    }
}

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
            fprintf(stderr, "FATAL ERROR: symbol \"%s\" already defined\n", lexeme);
            error_count++;
        }

        match(ID);
        parmlist();
        if (isfunc)
        {
            match(':');
            type();
            symtab[first_func_pro_index].type = current_type;
            symtab[first_func_pro_index].objtype = 1;
        }
        match(';');
        lexlevel++; // sobe o lexical level
        block();
        match(';');
        symtab_next_entry = first_func_pro_index + 1;
        lexlevel--; // desce o lexical level
    };
}

void beginend(void)
{
    match(BEGIN);
    stmtlst();
    match(END);
}

void stmtlst(void)
{
_stmtlst:
    stmt();
    if (lookahead == ';')
    {
        match(';');
        goto _stmtlst;
    }
}

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
        lexlevel++;
        int first_index = symtab_next_entry;
        idlist();
        lexlevel--;
        match(':');
        type();
        for (int i = first_index; i < symtab_next_entry; i++)
        {
            symtab[i].objtype = 2;
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

void idstmt(void)
{
    int id_position = symtab_lookup(lexeme, lexlevel);
    if (id_position < 0)
    {
        fprintf(stderr, "FATAL ERROR: symbol \"%s\" not defined\n", lexeme);
        error_count++;
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

void whlstmt(void)
{
    match(WHILE);
    expr();
    match(DO);
    stmt();
}

void repstmt(void)
{
    match(REPEAT);
    stmtlst();
    match(UNTIL);
    expr();
}

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

void term(void)
{
    factor();
    while (isotimes())
    {
        match(lookahead);
        factor();
    }
}

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

void expr(void)
{
    smpexpr();
    if (relop())
    {
        match(lookahead);
        smpexpr();
    }
}

int relop(void)
{
    switch (lookahead)
    {
    case LT:
    case LEQ:
    case EQ:
    case NEQ:
    case GEQ:
    case GT:
    case IN:
        return lookahead;
    default:
        return 0;
    }
}

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

void type(void)
{
    switch (lookahead)
    {
    case INTEGER:
        current_type = 0;
        match(lookahead);
        break;
    case REAL:
        current_type = 2;
        match(lookahead);
        break;
    case DOUBLE:
        current_type = 3;
        match(lookahead);
        break;
    default:
        current_type = 4;
        match(BOOLEAN);
    }
}

void match(int expected)
{
    if (lookahead == expected)
        lookahead = gettoken(source);
    else
    {
        fprintf(stderr, "Syntax error at line %d\n", linenum);
        exit(-3);
    }
}
