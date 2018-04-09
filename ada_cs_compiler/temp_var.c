#include "my_header.h"

char *get_temp(void) {
	/* max temporary allocated so far */
	static int max_temp = 0;
	static char tempname[MAXIDLEN];

	max_temp++;
	sprintf(tempname,"Temp&%d",max_temp);
	check_id(tempname);
	return tempname;
}
