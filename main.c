#include <stdio.h>
#include "lem_in.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>

/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

t_room     *lstnew(char *name, int x, int y, int start_end)
{
	t_room *result;

	result = (t_room *)malloc(sizeof(t_room));
	if (!result)
		return (NULL);
	result->x = x;
	result->y = y;
	result->name = (char *)malloc(sizeof(char) * (1 + ft_strlen(name)));
	result->name = ft_strcpy(result->name, name);
	result->start_end = start_end;
	result->next = NULL;
	return (result);
}

void		lstadd(t_room **result, t_room *new_result)
{
	t_room *elem;

	elem = NULL;
	elem = new_result;
	elem->next = *result;
	*result = elem;
}


int		count_digits_in_number1(int number)
{
	int i;

	i = 0;
	if (number < 0)
		number = number * (-1);
	while (number / 10 > 0)
	{
		number = number / 10;
		i++;
	}
	return (i + 1);
}


char	*return_substr(char *str, char c)
{
	int i;
	char *returned;

	i = 0;
	while (str[i] != c)
	{
		i++;
	}
	returned = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != c)
	{
		returned[i] = str[i];
		i++;
	}
	return (returned);
}



int 	count_symbol(const char *str, char chr)
{
	int i;
	int result;

	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == chr)
			result++;
		i++;
	}
	return (result);
}

int 	count_symbols_to_char(const char *str, char chr)
{
	int i;

	i = 0;
	while (str[i] != chr)
	{
		i++;
	}
	return (i);
}

void	get_room_name(const char *str, char **room_name, char chr)
{
	int i;

	i = 0;
	while (str[i] != chr)
	{
		(*room_name)[i] = str[i];
		i++;
	}
}

void	set_coord(t_room *room, char *str)
{
	int i;
	int j;

	i = 0;
	while  (str[i] != ' ')
		i++;
	i++;
	j = i;
	while (str[i] != ' ')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			;//error;
	}
	room->x = ft_atoi(str + j);
	i++;
	j = i;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			;//error;
	}
	room->y = ft_atoi(str + j);
}

int 	substr(char *str1, char *str2)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] == str2[j])
		{
			j = 0;
			k = i;
			while (str2[j] != '\0')
			{
				if (str2[j] == str1[k])
				{
					k++;
					j++;
				}
				else
					break ;
			}
			if (str2[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}





int 	symb_in_string(char *str, char chr)
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



void	add_room(char *line, t_room **room, int start_end)
{
	int i;
	char *name;
	int j;
	int x;
	int y;
	t_room *tmp_room;

	i = 0;
	j = 0;
	tmp_room = *room;
	while (line[i] != ' ')
		i++;
	name = (char *) malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		name[j] = line[j];
		j++;
	}
	name[j] = '\0';
	i++;
	j = i;
	if (line[i] == ' ')
		coord_error(name);
	while (line[i] != ' ')
	{
		if (line[i] < '0' || line[i] > '9')
			coord_error(name);
		i++;
	}
	x = ft_atoi(line + j);
	i++;
	j = i;
	while (line[i] != '\0')
	{
		if (line[i] < '0' || line[i] > '9')
			coord_error(name);
		i++;
	}
	y = ft_atoi(line + j);
	while (tmp_room->next != NULL)
	{
		if (tmp_room->x == x && tmp_room->y == y)
		{
			printf("%s %s %s %s\n", "SAME COORDINATES IN", name, "AND", tmp_room->name);
			exit(0);
		}
		if (ft_strcmp(tmp_room->name, name) == 0)
		{
			printf("%s %s\n", "EXIST AT LEAST TWO ROOMS WITH A NAME", name);
			exit(0);
		}
		tmp_room = tmp_room->next;
	}
	lstadd(room, lstnew(name, x, y, start_end));
}


int 	if_comment(char  *str)
{
	if (ft_strncmp(str, "#", 1) != 0)
		return (0);
	return (1);
}

t_names	*get_names(const char *line)
{
	int i;
	int j;
	int k;
	t_names *names;

	k = 0;
	i = 0;
	j = 0;
	names = (t_names *)malloc(sizeof(names));
	while (line[i] != '-')
		i++;
	names->name1 = (char *)malloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		names->name1[j] = line[j];
		j++;
	}
	i += 2;
	while (line[i] != '\0')
		i++;
	j += 1;
	names->name2 = (char *)malloc(sizeof(char) * (i - j - 1));
	while (j < i)
	{
		names->name2[k] = line[j];
		j++;
		k++;
	}
	return (names);
}

void	add_link(t_room **room, t_names *names)
{
	int i;
	t_room *room1;

	room1 = *room;

	while ((*room)->next != NULL)
	{
		i = 0;
		if (ft_strcmp(names->name1, (*room)->name) == 0)
		{
			while ((*room)->subrooms[i] != NULL)
				i++;
			(*room)->subrooms[i] = (char *)malloc(sizeof(char) * (ft_strlen(names->name2) + 1));
			ft_strcpy((*room)->subrooms[i], names->name2);
		}
		else if (ft_strcmp(names->name2, (*room)->name) == 0)
		{
			while ((*room)->subrooms[i] != NULL)
				i++;
			(*room)->subrooms[i] = (char *)malloc(sizeof(char) * (ft_strlen(names->name1) + 1));
			ft_strcpy((*room)->subrooms[i], names->name1);
		}
		(*room) = (*room)->next;
	}
	*room = room1;
//	if (ft_strcmp(names->name1, (*room)->name) == 0)
//	{
//		while ((*room)->subrooms[i] != NULL)
//			i++;
//		(*room)->subrooms[i] = (char *) malloc(sizeof(char) * (ft_strlen(names->name2) + 1));
//		ft_strcpy((*room)->subrooms[i], names->name2);
//	}
//	if (ft_strcmp(names->name2, (*room)->name) == 0)
//	{
//		while ((*room)->subrooms[i] != NULL)
//			i++;
//		(*room)->subrooms[i] = (char *) malloc(sizeof(char) * (ft_strlen(names->name1) + 1));
//		ft_strcpy((*room)->subrooms[i], names->name1);
//	}

}

void malloc_subrooms(t_room **room)
{
	int i;
	t_room *room1;
	t_room *room2;
	int j;

	j = 0;
	room1 = (*room);
	room2 = (*room);
	i = 0;

	while ((room1)->next != NULL)
	{
		i++;
		room1 = room1->next;
	}
	i++;
	while ((*room)->next != NULL)
	{
		(*room)->subrooms = (char**)malloc(sizeof(char*) * i);
		while (j <= i)
		{
			(*room)->subrooms[j] = NULL;
			j++;
		}
		(*room) = (*room)->next;
	}
	(*room)->subrooms = (char**)malloc(sizeof(char*) * i);
	(*room) = room2;
}


t_room 	*read_rooms(t_room *room)
{
	char *line;
	int fd;
	t_room *tmp_room;
	int start;
	int end;

	start = 0;
	end = 0;
	fd = open("file", O_RDONLY);
	room->next = NULL;
	while (get_next_line(fd, &line))
	{
		if (symb_in_string(line, ' ') == 2)
			add_room(line, &room, -1);
		else if (ft_strcmp(line, "##start") == 0)
		{
			get_next_line(fd, &line);
			if (symb_in_string(line, ' ') == 2)
				add_room(line, &room, 1);
			else
			{
				printf("%s", "WRONG LINE");
				exit(0);
			}
		}
		else if (ft_strcmp(line, "##end") == 0)
		{
			get_next_line(fd, &line);
			if (symb_in_string(line, ' ') == 2)
				add_room(line, &room, 0);
			else
			{
				printf("%s", "WRONG LINE");
				exit(0);
			}
		}
		else if (if_comment(line) == 1)
			continue;
		else if (symb_in_string(line, '-') == 1)
			break;
		else
		{
			printf("%s", "WRONG LINE");
			exit(0);
		}
	}
	tmp_room = room;
	while (tmp_room->next != NULL)
	{
		if (tmp_room->start_end == 1)
			start = 1;
		if (tmp_room->start_end == 0)
			end = 1;
		tmp_room = tmp_room->next;
	}
	if (tmp_room->start_end == 1)
		start = 1;
	if (tmp_room->start_end == 0)
		end = 1;
	if (start != 1 || end != 1)
	{
		printf("%s", "Start or end is missing");
		exit(0);
	}
	malloc_subrooms(&room);
	if (symb_in_string(line, '-') == 1)
		add_link(&room, get_names(line));
	else
	{
		printf("%s", "ERROR!");
		exit(0);
	}
	while (get_next_line(fd, &line))
	{

		if (if_comment(line) == 1)
			continue;
		else if (symb_in_string(line, '-') == 1)
		{
			add_link(&room, get_names(line));
		}
		else
		{
			printf("%s", "ERROR!");
			exit(0);
		}
	}
	return (room);
}













































int main()
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));

	room = read_rooms(room);
	printf("%s   %s\n", room->name, room->subrooms[0]);
	return 0;
}