/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 13:02:19 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/24 00:11:43 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		min_room(t_room *room)
{
	int i;
	int min;

	i = 0;
	if (room->tree[0] == NULL)
	{
		ft_printf("%s\n", "ERROR");
		exit(0);
	}
	min = room->tree[0]->length_to_room;
	while (room->tree[i] != NULL)
	{
		if (min > room->tree[i]->length_to_room)
			min = room->tree[i]->length_to_room;
		i++;
	}
	i = 0;
	while (room->tree[i] != NULL)
	{
		if (room->tree[i]->length_to_room == min)
			return (i);
		i++;
	}
	return (-1);
}

void	goround_rooms(t_room **room, int current_length)
{
	int i;

	i = 0;
	if ((*room)->length_to_room < current_length && (*room)->allready_was == 1)
		return ;
	else
	{
		(*room)->allready_was = 1;
		(*room)->length_to_room = current_length;
	}
	while ((*room)->tree[i] != NULL)
	{
		if ((*room)->tree[i]->length_to_room > current_length &&
		(*room)->tree[i]->allready_was != 1)
			(*room)->tree[i]->length_to_room = current_length + 1;
		i++;
	}
	i = 0;
	while ((*room)->tree[i] != NULL)
	{
		goround_rooms(&(*room)->tree[i], current_length + 1);
		i++;
	}
}

void	get_all_rooms(int ants, t_room **room)
{
	t_room *room2;
	t_room *room1;

	if (ants <= 0 || ants > 2147483647)
		wrong_ants_number();
	(*room) = read_rooms(*room);
	room1 = *room;
	while ((*room)->next->next != NULL)
		*room = (*room)->next;
	free((*room)->next->tree);
	free((*room)->next);
	(*room)->next = NULL;
	(*room) = room1;
	room2 = (*room);
	while (room2 != NULL)
	{
		room2->allready_was = 0;
		room2->length_to_room = 2147483647;
		room2->amount_of_ants = 0;
		room2->ant_number_current = 0;
		room2->ant_number_was = 0;
		room2 = room2->next;
	}
}

void	algorithm(t_room *room1, t_room *room, int ants)
{
	int i;
	int k;

	i = 1;
	k = room1->length_to_room;
	room1->amount_of_ants = ants;
	if (room1->tree[min_room(room1)]->length_to_room == 2147483647)
		ft_printf("%s\n", "ERROR");
	while (room1->amount_of_ants + k - 1 > 0)
	{
		room1->tree[min_room(room1)]->ant_number_was =
				room1->tree[min_room(room1)]->ant_number_current;
		room1->tree[min_room(room1)]->ant_number_current = i;
		i++;
		while (1)
		{
			if (print_ants(room, ants) == 1)
				break ;
		}
		room1->amount_of_ants--;
	}
}
