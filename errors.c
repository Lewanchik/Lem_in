
#include "lem_in.h"
#include <stdio.h>
#include <stdlib.h>

void coord_error(char *name)
{
	printf("%s %s %s", "Coord x or y in", name, "is not a number");
	exit(1);
}