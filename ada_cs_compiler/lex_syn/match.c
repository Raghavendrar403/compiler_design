/* this files matches the token with the syntax rules */
#include "my_header.h"
extern int in_char, c;
int match(token a) {

	switch(a) {
		
		case BEGIN:	
			if(next_token() == BEGIN) {
				printf("MATCHED BEGIN\n");
				return 1;
			}
			break;
			
		case END:
			if(!strcmp(token_buffer,"END")) {
				printf("MATCHED END\n");
				return 1;
			}
			else if(next_token() == END) {
				printf("MATCHED END\n");
				return 1;
			}
			break;

		case ID:
			if(check_reserved() == ID) {
				printf("MATCHED ID\n");
				return 1;
			}
			break;

		case LPAREN:
			if(in_char == '(') {
				printf("MATCHED LPAREN\n");
				return 1;
			}
			break;
			
		case RPAREN:
			if(in_char == ')') {
				printf("MATCHED RPAREN\n");
				return 1;
			}
			break;

		case COMMA:
			if(in_char == ',') {
				printf("MATCHED COMMA \n");
				return 1;
			}
			break;
		
		case SEMICOLON:
			if(in_char == ';') {
				printf("MATCHED SEMICOLON\n");
				return 1;
			}
			break;

		case ASSIGNOP:
			if(next_token() == ASSIGNOP) {
				printf("MATCHED ASSIGNOP\n");
				return 1;
			}
			break;

		case PLUSOP:
			if(in_char == '+') {
				printf("MATCHED PLUSOP\n");
				return 1;
			}
			break;

		case MINUSOP:
			if(in_char == '-' && c != '-') {
				printf("MATCHED MINUSOP\n");
				return 1;
			}
			break;

		case SCANEOF:
			if(next_token() == SCANEOF);
				return 1;
			break;

		case INTLITERAL:
			if(atoi(token_buffer)) {
				printf("MATCHED INTLITERAL\n");
				return 1;
			}
			break;

	}
	syntax_error(a);
}

void syntax_error(token a) {
	char error[100];
	switch(a) {
		case BEGIN:	strcpy(error, "BEGIN"); break;
		case END: strcpy(error, "END"); break;
		case LPAREN: strcpy(error,"("); break;
		case RPAREN: strcpy(error,")"); break;
		case SEMICOLON: strcpy(error,";"); break;
		case COMMA: strcpy(error,","); break;
		case ID: strcpy(error,"ID"); break; 
		case READ: strcpy(error,"READ"); break;
		case WRITE: strcpy(error,"WRITE"); break;
		default: strcpy(error,"RESERVED"); break;
	}
	printf("SYNTAX ERROR: Unable to match '%s' \n", error);
	exit(1);
}

token next_token() {
	return scanner();
}
