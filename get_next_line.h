/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 15:28:29 by ozalisky          #+#    #+#             */
/*   Updated: 2018/02/26 13:31:00 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1
# include "unistd.h"
# include "stdlib.h"
# include "./libft/libft.h"

int					get_next_line(const int fd, char **line);

typedef struct		s_gnl
{
	int				fd;
	char			*buffer;
	size_t			file_size;
	struct s_gnl	*next;
}					t_gnl;
#endif
