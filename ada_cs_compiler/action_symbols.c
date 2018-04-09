#include "my_header.h"

void start(void) {
	/* Semantic Initializations, none needed */
	generate("Start","","","");
}

void finish(void) {
	/* Generate Code to finish the program */
	generate("Halt", "", "", "");
}

void assign(expr_rec target, expr_rec source) {
	/* Generate code for assignment */
	generate("Store",extract(source), target.name, "");
}

op_rec process_op(token t) {
	/* Produce operator descriptor */
	op_rec o;

	if(t == PLUSOP)
		o.operator = PLUS;

	else 
		o.operator = MINUS;
	
	return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2) {
	expr_rec erec;
	/* An expr_rec with temp variant set. */
	erec.kind = TEMPEXPR;
	/* Generate code for infix operation.
	 * Get result temp and set up semantic record
	 * for result.
	 */

	strcpy(erec.name, get_temp());
	string a ; strcpy(a,extract(e1));
	string b ; strcpy(b,extract(e2));
	string c ; strcpy(c,extract_op(op));
	generate(c, a, b, erec.name);
	return erec;
}

void read_id(expr_rec in_var) {
	/* Generate code for read */
	generate("Read", in_var.name, "Integer","");
}

expr_rec process_id(void) {
	expr_rec t;
	/*
	 * Declare ID and build a corresponding 
	 * semantic record.
	 */

	 check_id(token_buffer);
	 t.kind = IDEXPR;
	 strcpy(t.name, token_buffer);
	 return t;
}

expr_rec process_literal(void) {
	expr_rec t;

	/*
	 * Convert literal to a numeric representation
	 * and build a semantic record
	 */
	 t.kind = LITERALEXPR;
	 t.val = atoi(token_buffer);
	 return t;
}

void write_expr(expr_rec out_rec) {
	generate("Write", extract(out_rec), "Integer", "");
}
