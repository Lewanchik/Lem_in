/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:53:47 by ozalisky          #+#    #+#             */
/*   Updated: 2017/11/16 15:01:13 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_neg_nbr(char *s, int n, int *min)
{
	char *c_s;

	c_s = s;
	*c_s = '-';
	if (n == -2147483648)
	{
		*min = 1;
		c_s++;
		*c_s = 2 + '0';
		n = -147483648;
	}
	n = -n;
	return (n);
}

static int		ft_rgt_nbr(int n)
{
	while (n >= 10)
		n %= 10;
	return (n);
}

static void		ft_nbr_less(char *s, int n, int i)
{
	int min;

	min = 0;
	n = ft_neg_nbr(s, n, &min);
	while (n >= 0 && i >= 1)
	{
		if (n >= 10)
		{
			s[i] = ft_rgt_nbr(n) + '0';
			n /= 10;
		}
		else if (n < 10 && i == 1 && min != 1)
			s[i] = n + '0';
		else if (n < 10 && i > 1)
			s[i] = n + '0';
		--i;
	}
}

static void		ft_nbr_more(char *s, int n, int i)
{
	while (n >= 0 && i >= 0)
	{
		if (n < 10)
			s[i] = n + '0';
		else if (n >= 10)
		{
			s[i] = ft_rgt_nbr(n) + '0';
			n /= 10;
		}
		--i;
	}
}

char			*ft_itoa(int n)
{
	char	*s;
	int		i;

	i = ft_nbr_lngth(n);
	if ((s = ft_strnew(i)) == NULL)
		return (NULL);
	s[i--] = '\0';
	if (n < 0)
		ft_nbr_less(s, n, i);
	else if (n > 0)
		ft_nbr_more(s, n, i);
	else
		s[i] = '0';
	return (s);
}
