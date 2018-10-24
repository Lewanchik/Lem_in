/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 11:14:03 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/24 00:04:36 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void		part_of_cycle1(t_ints **ints, t_room **room, t_room *room1,
		t_names
*names)
{
	t_room *tmp;

	(*ints)->j = 0;
	if ((*ints)->label == 0)
		(*room)->tree[(*ints)->i] = room1;
	(*ints)->label = 0;
	tmp = (*room);
	(*room) = (*ints)->start;
	while (ft_strcmp((*room)->name, room1->name) != 0 && *room != NULL)
		*room = (*room)->next;
	while ((*room)->tree[(*ints)->j] != NULL)
	{
		if (ft_strcmp((*room)->tree[(*ints)->j]->name, names->name1) == 0)
			(*ints)->label = 1;
		(*ints)->j++;
	}
	if ((*ints)->label == 0)
		(*room)->tree[(*ints)->j] = tmp;
	(*room) = tmp;
}

static void		part_of_cycle2(t_ints **ints, t_room **room, t_room *room1,
		t_names *names)
{
	t_room *tmp;

	(*ints)->j = 0;
	if ((*ints)->label == 0)
		(*room)->tree[(*ints)->i] = room1;
	(*ints)->label = 0;
	tmp = (*room);
	(*room) = (*ints)->start;
	while (ft_strcmp((*room)->name, room1->name) != 0 && *room != NULL)
		*room = (*room)->next;
	while ((*room)->tree[(*ints)->j] != NULL)
	{
		if (ft_strcmp((*room)->tree[(*ints)->j]->name, names->name2) == 0)
			(*ints)->label = 1;
		(*ints)->j++;
	}
	if ((*ints)->label == 0)
		(*room)->tree[(*ints)->j] = tmp;
	(*room) = tmp;
}

static	void	func1(t_ints **ints, t_room **room, t_names *names, t_room
*start)
{
	t_room *room1;

	room1 = start;
	(*ints)->label = 0;
	while ((*room)->tree[(*ints)->i] != NULL)
	{
		if (ft_strcmp((*room)->tree[(*ints)->i]->name, names->name2) == 0)
			(*ints)->label = 1;
		(*ints)->i++;
	}
	while (room1->next != NULL)
	{
		if (ft_strcmp(names->name2, room1->name) == 0)
		{
			part_of_cycle1(ints, room, room1, names);
			break ;
		}
		room1 = room1->next;
	}
}

static	void	func2(t_ints **ints, t_room **room, t_names *names, t_room
*start)
{
	t_room *room1;

	room1 = start;
	(*ints)->label = 0;
	while ((*room)->tree[(*ints)->i] != NULL)
	{
		if (ft_strcmp((*room)->tree[(*ints)->i]->name, names->name1) == 0)
			(*ints)->label = 1;
		(*ints)->i++;
	}
	while (room1->next != NULL)
	{
		if (ft_strcmp(names->name1, room1->name) == 0)
		{
			part_of_cycle2(ints, room, room1, names);
			break ;
		}
		room1 = room1->next;
	}
}

void			add_link(t_room **room, t_names *names)
{
	t_room *room2;
	t_ints *ints;

	ints = (t_ints *)ft_memalloc(sizeof(t_ints));
	room2 = *room;
	ints->start = *room;
	while ((*room)->next != NULL)
	{
		ints->i = 0;
		if (ft_strcmp(names->name1, (*room)->name) == 0)
			func1(&ints, room, names, room2);
		else if (ft_strcmp(names->name2, (*room)->name) == 0)
			func2(&ints, room, names, room2);
		(*room) = (*room)->next;
	}
	free(ints);
	*room = room2;
}
