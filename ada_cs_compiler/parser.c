#include "my_header.h"

void system_goal() {
	printf(" <system goal> -> <program> SCANEOF \n");
	program();
	//match(SCANEOF);
}

void program() {
	printf(" <program> -> BEGIN <statement> END \n");
	match(BEGIN);
	statement_list();
	match(END);
}

void statement_list() {
	printf(" <statement> -> <statement> { <statement> } \n");
	statement(NXTKN);	
	while(1) {
		switch(next_token()) {
			case ID: statement(ID); break;
			case READ: statement(READ); break;
			case WRITE: statement(WRITE); break;
			default: return;
		}
	}
}

void statement(token t) {
	if(t == NXTKN)
		t = next_token();
	
	switch(t) {
		case ID:	
			printf(" <statement> -> ID:=<expression>; \n");
			match(ASSIGNOP);		
			expression();
			match(SEMICOLON);
			break;

		case READ:
			printf(" <statement> -> READ(<id_list>) \n");
			t = next_token();
			match(LPAREN);
			id_list();
			match(RPAREN);
			(void)next_token();
			match(SEMICOLON);
			break;

		case WRITE:
			printf(" <statement> -> WRITE(<expr_list>) \n");
			match(LPAREN);
			expr_list();
			match(RPAREN);
			match(SEMICOLON);
			break;

		default:
			syntax_error(t);
			break;
	}
}

void id_list() {
	printf(" <id list> -> ID{, ID} \n");
	(void)next_token();
	match(ID);	
	while(next_token() == COMMA) {
		match(COMMA);
		(void)next_token();
		match(ID);	
	}
}

void expr_list() {
	printf(" <expr list> -> <expression>{, <expression>} \n");
	expression();
	while(next_token() == COMMA) {
		expression();	
	}
}

void expression() {
	printf(" <expression> -> <primary>{<add op><primary>} \n");
	primary();
	token t = next_token();	
	while(t == PLUSOP || t == MINUSOP) {
		add_op(t);
		primary();
		t = next_token();
	}
}

void add_op(token t) {
	printf(" <add op> -> + | - \n");
	if(t == PLUSOP || t == MINUSOP) {
		match(t);
	}
	else
		syntax_error(t);
}

void primary() {
	token t = next_token();	
	switch(t) {
		case LPAREN:
			printf(" <primary> -> (<expression>) \n");
			match(LPAREN);
			expression();
			match(RPAREN);
			break;	

		case ID:
			printf(" <primary> -> ID \n");
			match(ID);
			break;

		case INTLITERAL:
			printf(" <primary> -> INTLITERAL \n");
			match(INTLITERAL);
			break;

		default:
			syntax_error(t);
	}
}

int main(int argc, char *arrgv[]) {
	system_goal();	
}
