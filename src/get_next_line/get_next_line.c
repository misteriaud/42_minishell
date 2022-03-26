/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:51:34 by artblin           #+#    #+#             */
/*   Updated: 2022/01/07 03:09:03 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_delete(t_lst **list, const int fd)
{
	t_lst	*e;
	t_lst	*p;

	e = *list;
	p = NULL;
	while (e)
	{
		if (e->file == fd)
		{
			if (!p)
				*list = e->next;
			else if (e->next)
				p->next = e->next;
			else
				p->next = NULL;
			if (e->stash)
				free(e->stash);
			if (e->buffer)
				free(e->buffer);
			free(e);
			return ;
		}
		p = e;
		e = e->next;
	}
}

static t_lst	*ft_list(t_lst **list, const int fd)
{
	t_lst		*e;

	e = *list;
	while (e)
	{
		if (e->file == fd)
			return (e);
		e = e->next;
	}
	e = malloc(sizeof(t_lst));
	if (e)
	{
		e->buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (e->buffer)
		{
			e->s = (!!(e->stash = NULL));
			e->file = fd;
			e->next = NULL;
			if (*list)
				e->next = *list;
			return (*list = e);
		}
		free(e);
	}
	return (NULL);
}

static t_bool	ft_read(t_lst *e)
{
	e->b = read(e->file, e->buffer, BUFFER_SIZE);
	if (e->b > 0)
		return (!(*(e->buffer + e->b) = '\0'));
	e->b = 0;
	return (FALSE);
}

static t_error	ft_line(t_lst *e)
{
	if (e->s && ft_search(e->stash, &e->x))
	{
		if (ft_subtract(e))
			return (ERROR);
		return (ft_rehash(e));
	}
	while (!e->line && ft_read(e))
	{
		if (ft_search(e->buffer, &e->x))
		{
			if (ft_generate(e))
				return (ERROR);
		}
		if (e->b)
		{
			if (ft_stock(e))
				return (ERROR);
		}
	}
	if (!e->line && e->s)
	{
		e->line = e->stash;
		e->s = (!!(e->stash = NULL));
	}
	return (!e->line);
}

char	*get_next_line(int fd)
{
	static t_lst	*list = NULL;
	t_lst			*e;

	if (fd >= 0)
	{
		e = ft_list(&list, fd);
		if (e)
		{
			e->line = NULL;
			if (!ft_line(e))
				return (e->line);
			ft_delete(&list, fd);
		}
	}
	return (NULL);
}
