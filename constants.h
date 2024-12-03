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

/* Constantes */

#define MAXIDLEN    32       // tamanho maximo de um identificador
#define MAXSTBSIZE  0x100000 // tamanho maximo da tabela de simbolos

/* Mensagens de erro */

#define TOO_MANY_ARGS_ERROR          "\033[31mERROR:\033[0m Too many arguments!\n"
#define FILE_ERROR                   "\033[31mERROR:\033[0m Please provide a .pas file to compile.\n"
#define SYNTAX_ERROR                 "\033[31mERROR:\033[0m Incorrect syntax near \"%s\".\t(ln:%d, col:%d)\n"
#define SYMBOL_ALREADY_DEFINED_ERROR "\033[31mERROR:\033[0m Symbol \"%s\" already defined.\t(ln:%d, col:%d)\n"
#define SYMBOL_NOT_FOUND_ERROR       "\033[31mERROR:\033[0m Symbol \"%s\" not defined.\t(ln:%d, col:%d)\n"
#define IDENTIFIER_NAME_ERROR        "\033[31mERROR:\033[0m Symbol name \"%s\" exceeds identifier length limit.\t(ln:%d, col:%d)\n"
#define UNTERMINED_COMMENT_ERROR     "\033[31mERROR:\033[0m Unterminated comment.\t(comment begins at line:%d)\n"