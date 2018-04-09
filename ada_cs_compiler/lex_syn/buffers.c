#include "my_header.h"

char *d = 0;

void buffer_char(char in_char) {
	if(!d) {
		d = token_buffer;	
	}
	*d++ = in_char;
}

void clear_buffer(void) {
	d = 0;
	int i = 0;
	for (i = 0; i<MAXTOKENLEN; i++)
		token_buffer[i] = 0;
}
