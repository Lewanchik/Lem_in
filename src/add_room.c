/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 11:58:33 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/23 23:39:49 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	init_and_nulling_ints(t_ints **ints, const char *line)
{
	*ints = (t_ints *)ft_memalloc(sizeof(t_ints));
	(*ints)->i = 0;
	(*ints)->j = 0;
	(*ints)->sign = 0;
	while (line[(*ints)->i] != ' ')
		(*ints)->i++;
}

static void	get_name(char **name, const char *line, t_ints **ints)
{
	while ((*ints)->j < (*ints)->i)
	{
		if (line[(*ints)->j] == '-')
		{
			ft_printf("%s\n", "At least one name has '-'");
			exit(0);
		}
		(*name)[(*ints)->j] = line[(*ints)->j];
		(*ints)->j++;
	}
	(*name)[(*ints)->j] = '\0';
	if ((*name)[0] == 'L')
	{
		ft_printf("%s %s %s", "Name", (*name), "has 'L' in start");
		exit(0);
	}
	(*ints)->i++;
	(*ints)->j = (*ints)->i;
	if (line[(*ints)->i] == '-')
	{
		(*ints)->sign = 1;
		(*ints)->i++;
		(*ints)->j++;
	}
}

static void	func(const char *line, t_ints **ints, const char *name)
{
	if (line[(*ints)->i] == ' ')
		coord_error(name);
	while (line[(*ints)->i] != ' ')
	{
		if (line[(*ints)->i] < '0' || line[(*ints)->i] > '9')
			coord_error(name);
		(*ints)->i++;
	}
	(*ints)->x = ft_atoi(line + (*ints)->j - (*ints)->sign);
	(*ints)->sign = 0;
	(*ints)->i++;
	(*ints)->j = (*ints)->i;
	if (line[(*ints)->i] == '-')
	{
		(*ints)->sign = 1;
		(*ints)->i++;
		(*ints)->j++;
	}
	while (line[(*ints)->i] != '\0')
	{
		if (line[(*ints)->i] < '0' || line[(*ints)->i] > '9')
			coord_error(name);
		(*ints)->i++;
	}
}

void		add_room(char *line, t_room **room, int start_end)
{
	t_room	*tmp_room;
	char	*name;
	t_ints	*ints;

	tmp_room = *room;
	init_and_nulling_ints(&ints, line);
	name = (char *)malloc(sizeof(char) * (ints->i + 1));
	get_name(&name, line, &ints);
	func(line, &ints, name);
	ints->y = ft_atoi(line + ints->j - ints->sign);
	while (tmp_room->next != NULL)
	{
		if (tmp_room->x == ints->x && tmp_room->y == ints->y)
			same_coords_error(name, tmp_room->name);
		if (ft_strcmp(tmp_room->name, name) == 0)
			two_name_error(name);
		tmp_room = tmp_room->next;
	}
	free(name);
	tmp_room = lstnew(name, ints->x, ints->y, start_end);
	lstadd(room, tmp_room);
	free(ints);
	free(ints->start);
}
