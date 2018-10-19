
#include "lem_in.h"
#include "get_next_line.h"

static void print_and_add(char *line, t_room **room, int start_end)
{
	printf("%s\n", line);
	add_room(line, room, start_end);
}

static void print_and_add_link(char *line, t_room **room)
{
	printf("%s\n", line);
	add_link(room, get_names(line));
}

static void  print_and_read(char **line)
{
	printf("%s\n", *line);
	get_next_line(0, line);
}

int     func(t_room **room, char **line)
{
	if (symb_in_string(*line, ' ') == 2)
		print_and_add(*line, room, -1);
	else if (ft_strcmp(*line, "##start") == 0)
	{
		print_and_read(line);
		if (symb_in_string(*line, ' ') == 2)
			print_and_add(*line, room, 1);
		else
			wrong_line_error();
	}
	else if (ft_strcmp(*line, "##end") == 0)
	{
		print_and_read(line);
		if (symb_in_string(*line, ' ') == 2)
			print_and_add(*line, room, 0);
		else
			wrong_line_error();
	}
	else if (if_comment(*line) == 1)
		return (1);
	else if (symb_in_string(*line, '-') == 1)
		return (2);
	else
		wrong_line_error();
	return (0);
}

static t_room   *return_func(t_room *tmp_room, t_room *room, char *line,
		t_ints *ints)
{
	while (tmp_room != NULL)
	{
		if (tmp_room->start_end == 1)
			ints->startt = 1;
		if (tmp_room->start_end == 0)
			ints->end = 1;
		tmp_room = tmp_room->next;
	}
	if (ints->startt != 1 || ints->end != 1)
		start_end_miss_error();
	malloc_subrooms(&room);
	if (symb_in_string(line, '-') == 1)
		print_and_add_link(line, &room);
	else
		wrong_line_error();
	while (get_next_line(0, &line))
	{
		if (if_comment(line) == 1)
			continue;
		else if (symb_in_string(line, '-') == 1)
			print_and_add_link(line, &room);
		else
			return (room);
	}
	return (room);
}

t_room 	*read_rooms(t_room *room)
{
	char	*line;
	t_room	*tmp_room;
	int     function;
	t_ints *ints;
	
	ints = (t_ints *)ft_memalloc(sizeof(t_ints));
	ints->startt = 0;
	ints->end = 0;
	room->next = NULL;
	while (get_next_line(0, &line))
	{
		function = func(&room, &line);
		if (function == 1)
			continue;
		else if (function == 2)
			break;
	}
	tmp_room = room;
	room = return_func(tmp_room, room, line, ints);
	return (room);
}
