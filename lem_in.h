/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 13:21:04 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/20 14:44:03 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "printf/ft_printf.h"

typedef	struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				start_end;
	int				length_to_room;
	char			allready_was;
	int				amount_of_ants;
	int				ant_number_was;
	int				ant_number_current;
	struct s_room	**tree;
	struct s_room	*next;
}					t_room;

typedef struct		s_ints
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		k;
	int		label;
	int		sign;
	int		startt;
	int		end;
	t_room	*start;
}					t_ints;

typedef struct		s_names
{
	char	*name1;
	char	*name2;
}					t_names;

void				print_and_add(char *line, t_room **room, int start_end);
void				wrong_ants_number(void);
void				init_and_nulling(t_ints **ints);
void				init_room(t_room **room);
int					symb_in_string(const char *str, char chr);
void				get_all_rooms(int ants, t_room **room);
void				algorithm(t_room *room1, t_room *room, int ants);
void				goround_rooms(t_room **room, int current_length);
int					min_room(t_room *room);
int					print_ants(t_room *room, int k);
t_room				*read_rooms(t_room *room);
int					if_comment(char *str);
void				malloc_subrooms(t_room **room);
t_names				*get_names(const char *line);
void				add_link(t_room **room, t_names *names);
void				add_room(char *line, t_room **room, int start_end);
t_room				*lstnew(char *name, int x, int y, int start_end);
void				lstadd(t_room **result, t_room *new_result);
void				start_end_miss_error(void);
void				wrong_line_error(void);
void				two_name_error(char *name);
void				same_coords_error(char *name1, char *name2);
void				coord_error(const char *name);

#endif
