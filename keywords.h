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
enum keywords
{
    BEGIN = 0X1000,
    PROGRAM,
    IF,
    THEN,
    ELSE,
    PROCEDURE,
    FUNCTION,
    WHILE,
    DO,
    REPEAT,
    UNTIL,
    VAR,
    IN,
    INTEGER,
    BOOLEAN,
    DOUBLE,
    REAL,
    END,
};

extern int iskeyword(char *);