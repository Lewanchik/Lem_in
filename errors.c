
#include "lem_in.h"
#include <stdio.h>
#include <stdlib.h>

void coord_error(const char *name)
{
	printf("%s %s %s", "Coord x or y in", name, "is not a number");
	exit(0);
}

void	same_coords_error(char *name1, char *name2)
{
	printf("%s %s %s %s\n", "SAME COORDINATES IN", name1, "AND", name2);
	exit(0);
}

void	two_name_error(char *name)
{
	printf("%s %s\n", "EXIST AT LEAST TWO ROOMS WITH A NAME", name);
	exit(0);
}

void	start_end_miss_error(void)
{
	printf("%s\n", "Start or end is missing");
	exit(0);
}

void	wrong_line_error(void)
{
	printf("%s\n", "Wrong line");
	exit(0);
}