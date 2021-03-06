#include "my_header.h"

void system_goal() {
	//printf(" <system goal> -> <program> SCANEOF \n");
	program();
	finish();
	match(SCANEOF);
}

void program() {
	//printf(" <program> -> BEGIN <statement> END \n");
	start();
	match(BEGIN);
	statement_list();
	match(END);
}

void statement_list() {
	//printf(" <statement> -> <statement> { <statement> } \n");
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
	expr_rec id;
	expr_rec *res = (expr_rec*) malloc(sizeof(expr_rec));
	switch(t) {
		case ID:	
			//printf(" <statement> -> ID:=<expression>; \n");
			id = process_id();
			match(ASSIGNOP);		
			expression(res);
			assign(id, *res);
			match(SEMICOLON);
			break;

		case READ:
			//printf(" <statement> -> READ(<id_list>) \n");
			t = next_token();
			match(LPAREN);
			id_list();
			match(RPAREN);
			(void)next_token();
			match(SEMICOLON);
			break;

		case WRITE:
			//printf(" <statement> -> WRITE(<expr_list>) \n");
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
	//printf(" <id list> -> ID{, ID} \n");
	(void)next_token();
	match(ID);	
	while(next_token() == COMMA) {
		match(COMMA);
		(void)next_token();
		match(ID);	
	}
}

void expr_list() {
	//printf(" <expr list> -> <expression>{, <expression>} \n");
	expr_rec *a;
	expression(a);
	while(next_token() == COMMA) {
		expression(a);	
	}
}

void expression(expr_rec *result) {
	static expr_rec left_operand, right_operand;
	op_rec op;
	//printf(" <expression> -> <primary>{<add op><primary>} \n");
	primary(&left_operand);
	token t = next_token();	
	while(t == PLUSOP || t == MINUSOP) {
		add_op(&op, t);
		primary(&right_operand);
		left_operand = gen_infix(left_operand, op, right_operand);
		t = next_token();
	}

	*result = left_operand;
}

void add_op(op_rec *op, token t) {
	//printf(" <add op> -> + | - \n");
	if(t == PLUSOP || t == MINUSOP) {
		match(t);
	}
	else
		syntax_error(t);
	*op = process_op(t);
}

void primary(expr_rec *operand) {
	token t = next_token();	
	switch(t) {
		case LPAREN:
			//printf(" <primary> -> (<expression>) \n");
			match(LPAREN);
			expression(operand);
			match(RPAREN);
			break;	

		case ID:
			//printf(" <primary> -> ID \n");
			match(ID);
			*operand = process_id();
			break;

		case INTLITERAL:
			//printf(" <primary> -> INTLITERAL \n");
			match(INTLITERAL);
			*operand = process_literal();
			break;

		default:
			syntax_error(t);
	}
}

int main(int argc, char *arrgv[]) {
	system_goal();	
}
