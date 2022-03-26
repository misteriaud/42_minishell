/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 05:10:48 by artblin           #+#    #+#             */
/*   Updated: 2021/12/18 06:59:37 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_error	ft_subtract(t_lst *e)
{
	e->line = malloc((e->x + 1) * sizeof(char));
	if (e->line)
	{
		*(e->line + e->x) = '\0';
		while (*(e->stash + (e->s - e->x)))
			*(e->line++) = *(e->stash++);
		e->stash -= e->x;
		e->line -= e->x;
		return (NOERR);
	}
	return (ERROR);
}

t_error	ft_rehash(t_lst *e)
{
	char	*new_stash;

	if (e->s - e->x)
	{
		new_stash = malloc(((e->s - e->x) + 1) * sizeof(char));
		if (new_stash)
		{
			*(new_stash + (e->s - e->x)) = '\0';
			while (*(e->stash + e->x))
				*(new_stash++) = *(e->stash++ + e->x);
			free(e->stash - (e->s - e->x));
			e->stash = new_stash - (e->s - e->x);
			e->s -= e->x;
			return (NOERR);
		}
		free(e->stash);
		e->stash = NULL;
		return (ERROR);
	}
	free(e->stash);
	e->stash = NULL;
	e->s = 0;
	return (NOERR);
}

t_error	ft_stock(t_lst *e)
{
	char				*new_stash;

	new_stash = malloc((e->s + e->b + 1) * sizeof(char));
	if (new_stash)
	{
		*(new_stash + (e->s + e->b)) = '\0';
		if (e->stash)
		{
			while (*(e->stash))
				*(new_stash)++ = *(e->stash++);
			free(e->stash - e->s);
		}
		while (*(e->buffer + e->x))
			*(new_stash)++ = *(e->buffer++ + e->x);
		e->stash = new_stash - (e->s + e->b);
		e->s = (e->s + e->b);
		e->buffer -= e->b;
		e->b = 0;
		return (NOERR);
	}
	if (e->line)
		free(e->line);
	e->line = NULL;
	return (ERROR);
}

t_error	ft_generate(t_lst *e)
{
	e->line = malloc((e->s + e->x + 1) * sizeof(char));
	if (e->line)
	{
		*(e->line + e->s + e->x) = '\0';
		if (e->stash)
		{
			while (*(e->stash))
				*(e->line++) = *(e->stash)++;
			free(e->stash - e->s);
			e->stash = NULL;
		}
		while (*(e->buffer + (e->b - e->x)))
			*(e->line++) = *(e->buffer++);
		e->line -= (e->s + e->x);
		e->buffer -= e->x;
		e->b -= e->x;
		e->s = 0;
		return (NOERR);
	}
	return (ERROR);
}

t_bool	ft_search(const char *str, size_t *x)
{
	*x = 0;
	if (str)
	{
		while (*str)
		{
			++(*x);
			if (*(str++) == '\n')
				return (TRUE);
		}
	}
	return ((*x = 0));
}
