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
		if (line[j] == '-')
		{
			printf("%s\n", "At least one name has '-'");
			exit(0);
		}
		name[j] = line[j];
		j++;
	}
	name[j] = '\0';
	if (name[0] == 'L')
	{
		printf("%s %s %s", "Name", name, "has 'L' in start");
		exit(0);
	}
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
			same_coords_error(name, tmp_room->name);
		if (ft_strcmp(tmp_room->name, name) == 0)
			two_name_error(name);
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

//void	add_link(t_room **room, t_names *names)
//{
//	int i;
//	t_room *room1;
//
//	room1 = *room;
//
//	while ((*room)->next != NULL)
//	{
//		i = 0;
//		if (ft_strcmp(names->name1, (*room)->name) == 0)
//		{
//			while ((*room)->subrooms[i] != NULL)
//				i++;
//			(*room)->subrooms[i] = (char *)malloc(sizeof(char) * (ft_strlen(names->name2) + 1));
//			ft_strcpy((*room)->subrooms[i], names->name2);
//		}
//		else if (ft_strcmp(names->name2, (*room)->name) == 0)
//		{
//			while ((*room)->subrooms[i] != NULL)
//				i++;
//			(*room)->subrooms[i] = (char *)malloc(sizeof(char) * (ft_strlen(names->name1) + 1));
//			ft_strcpy((*room)->subrooms[i], names->name1);
//		}
//		(*room) = (*room)->next;
//	}
//	*room = room1;
//}


void	add_link(t_room **room, t_names *names)
{
	int i;
	t_room *room1;
	t_room *room2;
	t_room *tmp;
	int j;

	room1 = *room;
	room2 = *room;
	while ((*room)->next != NULL)
	{
		i = 0;
		if (ft_strcmp(names->name1, (*room)->name) == 0)
		{
			while ((*room)->tree[i] != NULL)
				i++;
			while (room1->next != NULL)
			{
				if (ft_strcmp(names->name2, room1->name) == 0)
				{
					j = 0;
					(*room)->tree[i] = room1;
					tmp = (*room);
					(*room) = room2;
					while (ft_strcmp((*room)->name, room1->name) != 0)
						*room = (*room)->next;
					while ((*room)->tree[j] != NULL)
						j++;
					(*room)->tree[j] = tmp;
					(*room) = tmp;
					room1 = room2;
					break;
				}
				room1 = room1->next;
			}
		}
		else if (ft_strcmp(names->name2, (*room)->name) == 0)
		{
			while ((*room)->tree[i] != NULL)
				i++;
			while (room1->next != NULL)
			{
				if (ft_strcmp(names->name2, room1->name) == 0)
				{
					j = 0;
					(*room)->tree[i] = room1;
					tmp = (*room);
					(*room) = room2;
					while (ft_strcmp((*room)->name, room1->name) != 0)
						*room = (*room)->next;
					while ((*room)->tree[j] != NULL)
						j++;
					(*room)->tree[j] = tmp;
					(*room) = tmp;
					room1 = room2;
					break;
				}
				room1 = room1->next;
			}
		}
		(*room) = (*room)->next;
	}

	*room = room2;
}

//void malloc_subrooms(t_room **room)
//{
//	int i;
//	t_room *room1;
//	t_room *room2;
//	int j;
//
//	j = 0;
//	room1 = (*room);
//	room2 = (*room);
//	i = 0;
//
//	while ((room1)->next != NULL)
//	{
//		i++;
//		room1 = room1->next;
//	}
//	i++;
//	while ((*room)->next != NULL)
//	{
//		(*room)->subrooms = (char**)malloc(sizeof(char*) * i);
//		while (j <= i)
//		{
//			(*room)->subrooms[j] = NULL;
//			j++;
//		}
//		(*room) = (*room)->next;
//	}
//	(*room)->subrooms = (char**)malloc(sizeof(char*) * i);
//	(*room) = room2;
//}

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
		(*room)->tree = (t_room**)malloc(sizeof(t_room*) * i);

		while (j <= i)
		{
			(*room)->tree[j] = NULL;
			j++;
		}
		(*room) = (*room)->next;
	}

	(*room)->tree = (t_room**)malloc(sizeof(t_room *) * i);
	(*room) = room2;
}


t_room 	*read_rooms(t_room *room)
{
	char *line;
	t_room *tmp_room;
	int start;
	int end;

	start = 0;
	end = 0;
	room->next = NULL;
	while (get_next_line(0, &line))
	{
		if (symb_in_string(line, ' ') == 2)
			add_room(line, &room, -1);
		else if (ft_strcmp(line, "##start") == 0)
		{
			get_next_line(0, &line);
			if (symb_in_string(line, ' ') == 2)
				add_room(line, &room, 1);
			else
				wrong_line_error();
		}
		else if (ft_strcmp(line, "##end") == 0)
		{
			get_next_line(0, &line);
			if (symb_in_string(line, ' ') == 2)
				add_room(line, &room, 0);
			else
				wrong_line_error();
		}
		else if (if_comment(line) == 1)
			continue;
		else if (symb_in_string(line, '-') == 1)
			break;
		else
			wrong_line_error();
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
		start_end_miss_error();
	malloc_subrooms(&room);
	if (symb_in_string(line, '-') == 1)
		add_link(&room, get_names(line));
	else
		wrong_line_error();
	while (get_next_line(0, &line))
	{
		if (if_comment(line) == 1)
			continue;
		else if (symb_in_string(line, '-') == 1)
		{
			add_link(&room, get_names(line));
		}
		else
			wrong_line_error();
	}
	return (room);
}

//t_room	*make_tree(t_room *room)
//{
//	int i;
//	t_room *room1;
//	t_room *room2;
//	int j;
//
//	room1 = room;
//	room2 = room;
//	while (room->next != NULL)
//	{
//		i = 0;
//		j = 0;
//		room->tree = (t_room **)malloc(sizeof(t_room *) * 20);
//		while (room->subrooms[i] != NULL)
//		{
//			while(room1->next != NULL)
//			{
//				printf("%s  %s %d %d\n", room->subrooms[i], room->name, i, j);
//				if (ft_strcmp(room1->name, room->subrooms[i]) == 0)
//				{
//					printf("!\n");
//					room->tree[j] = (t_room *)malloc(sizeof(t_room));
//					printf("@!@\n");
//					room->tree[j] = room1;
//					printf("@@!@@\n");
//					j++;
//					room1 = room2;
//					break;
//				}
//				room1 = room1->next;
//			}
//			printf("@@@!@@@\n");
//
//			i++;
//		}
//		printf("!%s  %s %d %d!\n", room->subrooms[i], room->name, i, j);
//		room = room->next;
//	}
//	room = room2;
//	return (room);
//}
//










































int main()
{
	t_room *room;

	room = (t_room*)malloc(sizeof(t_room));
	room = read_rooms(room);

	printf("%s \n", room->next->tree[0]->name);
	return 0;
}