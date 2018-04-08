#include "my_header.h"
int in_char, c;

token scanner(void) {
	clear_buffer();
	if(feof(stdin))
		return SCANEOF;
	
	while((in_char = getchar()) != EOF)	{
		if(isspace(in_char) || in_char == '\n')
			continue; /* do nothing; */
			
		else if (isalpha(in_char)) {
			/* code to recognize indentifiers */
			buffer_char(in_char);
			for(c = getchar(); isalnum(c) || c == '_'; c = getchar())
				buffer_char(c);

			ungetc(c, stdin);
			return check_reserved();
			/* check_reserved checks whether the identifier is a reserved keyword or not */
		}
		else if (isdigit(in_char)) {
			/* code to recognize int literals */
			buffer_char(in_char);
			for(c = getchar(); isdigit(c); c = getchar())
				buffer_char(c);

			ungetc(c,stdin);
			return INTLITERAL;
		}
		else if (in_char == '(')
			return LPAREN;
		else if (in_char == ')')
			return RPAREN;
		else if (in_char == ';')
			return SEMICOLON;
		else if (in_char == ',')
			return COMMA;
		else if (in_char == '+')
			return PLUSOP;
		else if (in_char == ':') {
			/* looking for := operator */
			c = getchar();
			if (c == '=')
				return ASSIGNOP;
			else {
				ungetc(c, stdin);
				lexical_error(in_char);
			}
		} else if (in_char == '-')	 {
			/* looking for -- comment */
			c = getchar();
			if(c == '-') {
				while ((in_char = getchar()) != '\n') ;
			} else {
				ungetc(c, stdin);	
				return MINUSOP;
			}
		} else 
			lexical_error(in_char);
	}
}

void lexical_error(char in_char) {
	printf("LEXICAL ERROR: %c \n", in_char);
	exit(1);
}
