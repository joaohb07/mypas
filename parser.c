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
    match('.');
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

        match(lookahead); // match procedure ou function
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

void idstmt()
{
    match(ID);
    if (lookahead == ASGN) // DA PRA APROVEITAR O DO MYBC
    {
        match(ASGN);
        expr();
    }
    /* OBS NÃO UTILIZAREMOS PROCEDURE IDENTIFIER*/
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
        match(ID); // it can be variable or func identifier
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

/*
  TO DO: verificar e corrigir expr(), relop() e simpleExpr caso necessário
*/

void expr(void)
{
    simpleExpr();
    if (relop())
    {
        simpleExpr();
    }
}

int relop(void)
{
    switch (lookahead)
    {
    case LT:
        match(LT);
        return LT;
    case LEQ:
        match(LEQ);
        return LEQ;
    case EQ:
        match(EQ);
        return EQ;
    case NEQ:
        match(NEQ);
        return NEQ;
    case GEQ:
        match(GEQ);
        return GEQ;
    case GT:
        match(GT);
        return GT;
    case IN:
        match(IN);
        return IN;
    default:
        return 0;
    }
}

void simpleExpr(void)
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
  TO DO: implementar isotimes();
*/
int isotimes(void) { return 0; }

/*
  TO DO: implementar isoplus();
*/
int isoplus(void) { return 0; }

void type()
{
    // match(int ou  real (float) ou  double ou boolean)
    switch(lookahead) {
        case INTEGER:
        case REAL:
        case DOUBLE:
            match(lookahead);
            break;
        default:
            match(BOOLEAN);
    }
}

/*
    match compara o valor de lookahead com um valor esperado
*/
void match(int expected)
{
    if (lookahead == expected)
        lookahead = gettoken(source);
    else
    {
        fprintf(stderr, "syntax error at line %d: expected %d (%c), got %d (%c).\n", linenum,expected, expected, lookahead, lookahead);
        exit(-3);
    }
}
