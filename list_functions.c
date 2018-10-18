
#include "lem_in.h"


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
