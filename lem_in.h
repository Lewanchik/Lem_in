
#ifndef LEM_IN_H
# define LEM_IN_H

typedef  struct s_room
{
	char *name;
	int x;
	int y;
	int start_end;
	char **subrooms;
	struct s_room *next;
}				t_room;

typedef struct s_names
{
	char *name1;
	char *name2;
}				t_names;

void coord_error(char *name);

#endif