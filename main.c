#include <stdio.h>
#include "lem_in.h"
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>

/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

int 	symb_in_string(const char *str, char chr)
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

int 	if_comment(char  *str)
{
	if (ft_strncmp(str, "#", 1) != 0)
		return (0);
	return (1);
}

void	goround_rooms(t_room **room, int current_length)
{
	int i;

	i = 0;
	if ((*room)->length_to_room < current_length && (*room)->allready_was == 1)
		return;
	else
	{
		(*room)->allready_was = 1;
		(*room)->length_to_room = current_length;
	}
	while ((*room)->tree[i] != NULL)
	{
		if ((*room)->tree[i]->length_to_room > current_length && (*room)->tree[i]->allready_was != 1)
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

void    init_and_nulling(t_ints **ints)
{
	(*ints) = (t_ints *)ft_memalloc(sizeof(t_ints));
	(*ints)->k = 0;
	(*ints)->i = 0;
	(*ints)->j = 0;
}

t_names	*get_names(const char *line)
{
	t_ints *ints;
	t_names *names;
	
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
	return (names);
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
	while ((*room) != NULL)
	{
		(*room)->tree = (t_room**)malloc(sizeof(t_room*) * i);
		while (j <= i)
		{
			(*room)->tree[j] = NULL;
			j++;
		}
		j = 0;
		(*room) = (*room)->next;
	}
	(*room) = room2;
}

int	read_ants()
{
	char *line;
	int i;

	i = 0;
	get_next_line(0, &line);
	while (line[i] != 0)
	{
		if (line[i] < '0' || line[i] > '9')
		{
			wrong_line_error();
		}
		i++;
	}
	printf("%s\n", line);
	return (ft_atoi(line));
}

t_room 	*read_rooms(t_room *room)
{
	char	*line;
	t_room	*tmp_room;
	int		start;
	int		end;

	start = 0;
	end = 0;
	room->next = NULL;

	while (get_next_line(0, &line))
	{
		if (symb_in_string(line, ' ') == 2)
		{
			add_room(line, &room, -1);
			printf("%s\n", line);
		}
		else if (ft_strcmp(line, "##start") == 0)
		{
			printf("%s\n", line);
			get_next_line(0, &line);
			if (symb_in_string(line, ' ') == 2)
			{
				add_room(line, &room, 1);
				printf("%s\n", line);
			}
			else
				wrong_line_error();
		}
		else if (ft_strcmp(line, "##end") == 0)
		{
			printf("%s\n", line);
			get_next_line(0, &line);
			if (symb_in_string(line, ' ') == 2)
			{
				add_room(line, &room, 0);
				printf("%s\n", line);
			}
			else
				wrong_line_error();
		}
		else if (if_comment(line) == 1)
		{
			printf("%s\n", line);
			continue;
		}
		else if (symb_in_string(line, '-') == 1)
			break;
		else
			wrong_line_error();
	}
	tmp_room = room;
	while (tmp_room != NULL)
	{
		if (tmp_room->start_end == 1)
			start = 1;
		if (tmp_room->start_end == 0)
			end = 1;
		tmp_room = tmp_room->next;
	}
	if (start != 1 || end != 1)
		start_end_miss_error();
	malloc_subrooms(&room);
	if (symb_in_string(line, '-') == 1)
	{
		printf("%s\n", line);
		add_link(&room, get_names(line));
	}
	else
		wrong_line_error();
	while (get_next_line(0, &line))
	{
		if (if_comment(line) == 1)
		{
			printf("%s\n", line);
			continue;
		}
		else if (symb_in_string(line, '-') == 1)
		{
			printf("%s\n", line);
			add_link(&room, get_names(line));
		}
		else
			return (room);
	}
	return (room);
}


int 	min_room(t_room *room)
{
	int i;
	int min;

	i = 0;
	if (room->tree[0] == NULL)
	{
		printf("%s\n", "ERROR");
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

int		print_ants(t_room *room, int k)
{
	int		label;
	t_room	*room_tmp;
	int		room_min;

	room_tmp = room;
	label = 0;
	while (room != NULL)
	{
		if (room->ant_number_was != 0)
		{
			label = 1;
			room_min = min_room(room);
			if (room->start_end == 0)
			{
				room->amount_of_ants++;
				label = 0;
				room->ant_number_was = 0;
				break;
			}
			room->tree[room_min]->ant_number_was = room->tree[room_min]->ant_number_current;
			room->tree[room_min]->ant_number_current = room->ant_number_was;
			room->ant_number_was = 0;
		}
		room = room->next;
	}
	if (label == 0)
	{
		while(room_tmp != NULL)
		{
			if (room_tmp->ant_number_current != 0)
			{
				if (room_tmp->ant_number_current > k)
					break;
				printf("L%d-%s ", room_tmp->ant_number_current, room_tmp->name);
			}
			room_tmp = room_tmp->next;
		}
		printf("\n");
		return (1);
	}
	return (0);
}

int main()
{
	t_room *room;
	t_room *room1;
	t_room *room2;
	int i;
	int k;
	int length;
	int ants;

	room = (t_room*)malloc(sizeof(t_room));
	room->start_end = 3;
	room->name = NULL;
	room->tree = NULL;
	room->x = 0;
	room->y = 0;
	room->allready_was = 0;
	ants = read_ants();
	if (ants <= 0 || ants >= 2147483647)
		wrong_line_error();
	room = read_rooms(room);
	room1 = room;
	while (room->next->next != NULL)
		room = room->next;
	room->next = NULL;
	room = room1;
	room2 = room;
	while (room2 != NULL)
	{
		room2->allready_was = 0;
		room2->length_to_room = 2147483647;
		room2->amount_of_ants = 0;
		room2->ant_number_current = 0;
		room2->ant_number_was = 0;
		room2 = room2->next;
	}
	room1 = room;
	while (room1 != NULL)
	{
		if (room1->start_end == 0)
		{
			break;
		}
		room1 = room1->next;
	}
	goround_rooms(&room1, 0);

	room1 = room;
	while (room1 != NULL)
	{
		if (room1->start_end == 1)
		{
			break;
		}
		room1 = room1->next;
	}
	printf("\n");
	room1->amount_of_ants = ants;
	i = 1;
	k = room1->length_to_room;
	if (room1->tree[min_room(room1)]->length_to_room == 2147483647)
		printf("%s\n", "ERROR");
	while (room1->amount_of_ants + k - 1 > 0)
	{
		room1->tree[min_room(room1)]->ant_number_was = room1->tree[min_room(room1)]->ant_number_current;
		room1->tree[min_room(room1)]->ant_number_current = i;
		i++;
		while (1)
		{
			if (print_ants(room, ants) == 1)
				break;
		}
		room1->amount_of_ants--;
	}
	return 0;
}