/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:47:47 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/24 00:17:34 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

t_names		*get_names(const char *line)
{
	t_ints	*ints;
	t_names	*names;

	names = (t_names *)ft_memalloc(sizeof(t_names));
	init_and_nulling(&ints);
	while (line[ints->i] != '-')
		ints->i++;
	names->name1 = (char *)malloc(sizeof(char) * (ints->i + 1));
	while (ints->j < ints->i)
	{
		names->name1[ints->j] = line[ints->j];
		ints->j++;
	}
	ints->i += 2;
	while (line[ints->i] != '\0')
		ints->i++;
	ints->j += 1;
	names->name2 = (char *)malloc(sizeof(char) * (ints->i - ints->j - 1));
	while (ints->j < ints->i)
	{
		names->name2[ints->k] = line[ints->j];
		ints->j++;
		ints->k++;
	}
	free(ints);
	return (names);
}

static void	init_ints(t_ints **ints)
{
	*ints = (t_ints *)ft_memalloc(sizeof(t_ints));
	(*ints)->i = 0;
	(*ints)->j = 0;
}

void		malloc_subrooms(t_room **room)
{
	t_room	*room1;
	t_room	*room2;
	t_ints	*ints;

	room1 = (*room);
	room2 = (*room);
	init_ints(&ints);
	while ((room1)->next != NULL)
	{
		ints->i++;
		room1 = room1->next;
	}
	while ((*room) != NULL)
	{
		(*room)->tree = (t_room**)malloc(sizeof(t_room*) * ints->i);
		while (ints->j <= ints->i)
		{
			(*room)->tree[ints->j] = NULL;
			ints->j++;
		}
		ints->j = 0;
		(*room) = (*room)->next;
	}
	(*room) = room2;
	free(ints);
}

int			read_ants(void)
{
	char	*line;
	int		i;
	int		atoi_res;

	i = 0;
	get_next_line(0, &line);
	while (line[i] != 0)
	{
		if (line[i] < '0' || line[i] > '9')
		{
			free(line);
			wrong_ants_number();
		}
		i++;
	}
	printf("%s\n", line);
	atoi_res = ft_atoi(line);
	free(line);
	return (atoi_res);
}

void 	free_room(t_room **room)
{
	t_room *room1;

	while (*room != NULL)
	{
		room1 = (*room)->next;
		free((*room)->name);
		free((*room)->tree);
		free(*room);
		*room = room1;
	}
}

int			main(void)
{
	t_room	*room;
	t_room	*room1;
	int		ants;

	init_room(&room);
	ants = read_ants();
	get_all_rooms(ants, &room);
	room1 = room;
	while (room1 != NULL)
	{
		if (room1->start_end == 0)
			break ;
		room1 = room1->next;
	}
	goround_rooms(&room1, 0);
	room1 = room;
	while (room1 != NULL)
	{
		if (room1->start_end == 1)
			break ;
		room1 = room1->next;
	}
	ft_printf("\n");
	algorithm(room1, room, ants);
	free_room(&room);
	return (0);
}
