/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlewando <dlewando@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 16:13:38 by dlewando          #+#    #+#             */
/*   Updated: 2018/01/14 14:11:19 by dlewando         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1


# include "./libft.h"

typedef struct	s_lstr
{
	int				save_fd;
	size_t			buf_s;
	char			*buf;
	struct s_lstr	*next;
}				t_lstr;

int				get_next_line(const int fd, char **line);
#endif
