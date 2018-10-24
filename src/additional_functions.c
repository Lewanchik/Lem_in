/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:53:47 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/20 12:56:57 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		symb_in_string(const char *str, char chr)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			j++;
		i++;
	}
	return (j);
}

void	print_and_add(char *line, t_room **room, int start_end)
{
	ft_printf("%s\n", line);
	add_room(line, room, start_end);
	free(line);
}

int		if_comment(char *str)
{
	if (ft_strncmp(str, "#", 1) != 0)
		return (0);
	ft_printf("%s\n", str);
	return (1);
}

void	init_and_nulling(t_ints **ints)
{
	(*ints) = (t_ints *)ft_memalloc(sizeof(t_ints));
	(*ints)->k = 0;
	(*ints)->i = 0;
	(*ints)->j = 0;
}

void	init_room(t_room **room)
{
	(*room) = (t_room*)ft_memalloc(sizeof(t_room));
	(*room)->start_end = 3;
	(*room)->name = NULL;
	(*room)->tree = NULL;
	(*room)->x = 0;
	(*room)->y = 0;
	(*room)->allready_was = 0;
}
