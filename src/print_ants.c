/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:05:49 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/20 14:48:20 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int	func(int label, t_room **room)
{
	int room_min;

	while ((*room) != NULL)
	{
		if ((*room)->ant_number_was != 0)
		{
			label = 1;
			room_min = min_room((*room));
			if ((*room)->start_end == 0)
			{
				(*room)->amount_of_ants++;
				label = 0;
				(*room)->ant_number_was = 0;
				break ;
			}
			(*room)->tree[room_min]->ant_number_was =
					(*room)->tree[room_min]->ant_number_current;
			(*room)->tree[room_min]->ant_number_current =
					(*room)->ant_number_was;
			(*room)->ant_number_was = 0;
		}
		(*room) = (*room)->next;
	}
	return (label);
}

int			print_ants(t_room *room, int k)
{
	int		label;
	t_room	*room_tmp;

	room_tmp = room;
	label = 0;
	label = func(label, &room);
	if (label == 0)
	{
		while (room_tmp != NULL)
		{
			if (room_tmp->ant_number_current != 0)
			{
				if (room_tmp->ant_number_current > k)
					break ;
				ft_printf("L%d-%s ", room_tmp->ant_number_current,
						room_tmp->name);
			}
			room_tmp = room_tmp->next;
		}
		ft_printf("\n");
		return (1);
	}
	return (0);
}
