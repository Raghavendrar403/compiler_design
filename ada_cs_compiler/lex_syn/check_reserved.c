#include "my_header.h"

token check_reserved() {
	if(!strcmp("BEGIN",token_buffer))
		return BEGIN;
	else if(!strcmp("END",token_buffer))
		return END;
	else if(!strcmp("READ",token_buffer))
		return READ;
	else if(!strcmp("WRITE",token_buffer))
		return WRITE;
	else
		return ID;
}
