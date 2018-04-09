#include "my_header.h"

int lookup(string s) {
	int i = 0;
	for(i = 0; i<20; i++) {
		if(!strcmp(sym_tab[i],s))
			return 1;
	}

	return 0;
}

void enter(string s) {
	static int i = 0;
	strcpy(sym_tab[i],s);
	i++;
}

void check_id(string s) {
	if(!lookup(s)) {
		enter(s);
		generate("Declare",s,"Integer","");
	}
}

void generate(string s1, string s2, string s3, string s4) {
	printf("%s %s %s %s\n",s1,s2,s3,s4);
}

char *extract_op(op_rec op) {
	static char A[10];
	if(op.operator == PLUS) {
		strcpy(A,"Add");
	}

	else if(op.operator == MINUS) {
		strcpy(A,"Subtract");
	}

	return A;
}

char *extract(expr_rec rec) {
	static char B[10];
	if(rec.kind == LITERALEXPR) {
		sprintf(B,"%d",rec.val);
		return B;
	}
	strcpy(B, rec.name);
	return B;
}
