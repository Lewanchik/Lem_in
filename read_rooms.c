
#include "lem_in.h"
#include "get_next_line.h"

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
