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
#include <lexer.h>
#include <parser.h>

int lookahead;

void program(void)
{

    match(PROGRAM);
    match(ID);
    match('(');
    idlist();
    match(')');
    match(';');
    block();
    match('.');
}

void idlist(void)
{

_idlist:
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
        idlist();
        match(':');
        type();
        match(';');
        if (lookahead == ID)
            goto _idlist;
    }
}

void sbprgdef(void)
{
    while (lookahead == PROCEDURE || lookahead == FUNCTION)
    {
        int isfunc = (lookahead == FUNCTION);

        match(lookahead);
        match(ID);
        parmlist();
        if (isfunc)
        {
            match(':');
            type();
        }
        match(';');
        block();
        match(';');
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
        idlist();
        match(':');
        type();
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
        exprlist();
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

void type()
{
    switch (lookahead)
    {
    case INTEGER:
    case REAL:
    case DOUBLE:
        match(lookahead);
        break;
    default:
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
