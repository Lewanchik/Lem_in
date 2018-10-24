/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:09:50 by dlewando          #+#    #+#             */
/*   Updated: 2018/10/20 14:44:03 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	coord_error(const char *name)
{
	ft_printf("\n%s %s %s", "Coord x or y in", name, "is not a number");
	exit(0);
}

void	same_coords_error(char *name1, char *name2)
{
	ft_printf("\n%s %s %s %s\n", "Same coordinates in", name1, "and", name2);
	exit(0);
}

void	two_name_error(char *name)
{
	ft_printf("\n%s %s\n", "Exist at least two rooms with a name", name);
	exit(0);
}

void	start_end_miss_error(void)
{
	ft_printf("\n%s\n", "Start or end is missing");
	exit(0);
}

void	wrong_line_error(void)
{
	ft_printf("\n%s\n", "Wrong line");
	exit(0);
}
