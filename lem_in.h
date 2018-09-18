
#ifndef LEM_IN_H
# define LEM_IN_H

typedef  struct s_room
{
	char *name;
	int x;
	int y;
	int start_end;
	char **subrooms;
	struct s_room **tree;
	struct s_room *next;
}				t_room;


typedef struct s_names
{
	char *name1;
	char *name2;
}				t_names;

void	start_end_miss_error(void);
void	wrong_line_error(void);
void	two_name_error(char *name);
void	same_coords_error(char *name1, char *name2);
void coord_error(char *name);

#endif