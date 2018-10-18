
#ifndef LEM_IN_H
# define LEM_IN_H

#include <stdio.h>
#include  "libft.h"

typedef  struct s_room
{
	char    *name;
	int     x;
	int y;
	int start_end;
	int length_to_room;
	char allready_was;
	int  amount_of_ants;
	int  ant_number_was;
	int  ant_number_current;
	struct s_room **tree;
	struct s_room *next;
}				t_room;

typedef struct  s_ints
{
	int i;
	int j;
	int x;
	int y;
	int k;
	int label;
	int sign;
	t_room *start;
}               t_ints;


typedef struct s_names
{
	char *name1;
	char *name2;
}				t_names;

int 	symb_in_string(const char *str, char chr);
int 	if_comment(char  *str);
void malloc_subrooms(t_room **room);
t_names	*get_names(const char *line);
void	    add_link(t_room **room, t_names *names);
void	    add_room(char *line, t_room **room, int start_end);
t_room     *lstnew(char *name, int x, int y, int start_end);
void		lstadd(t_room **result, t_room *new_result);
void	start_end_miss_error(void);
void	wrong_line_error(void);
void	two_name_error(char *name);
void	same_coords_error(char *name1, char *name2);
void 	coord_error(const char *name);

#endif