#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAXTOKENLEN 100

typedef enum token_types {
	BEGIN, END, READ, WRITE, ID, INTLITERAL,
	LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP, 
	PLUSOP, MINUSOP, SCANEOF, NXTKN
} token;

char token_buffer[MAXTOKENLEN];

extern token scanner(void);
extern void lexical_error(char);
extern void buffer_char(char);
extern void clear_buffer(void);
extern int match(token);
extern token check_reserved(void);
extern token next_token(void);
extern void syntax_error(token);
void system_goal(void);
void statement_list(void);
void program(void);
void statement(token);
void id_list(void);
void expr_list(void);
void expression(void);
void add_op(token);
void primary(void);
