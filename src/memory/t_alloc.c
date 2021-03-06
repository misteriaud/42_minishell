/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_alloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:31:02 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/10 15:42:57 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory.h>

t_alloc	**get_first_alloc(int group)
{
	t_node	*node;

	node = get_node(group);
	if (!node)
		return (NULL);
	return (&node->first);
}

t_alloc	*new_alloc(t_alloc **first, size_t size)
{
	t_alloc	*dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->ptr = malloc(size);
	if (!dest->ptr)
	{
		free(dest);
		return (NULL);
	}
	dest->next = *first;
	dest->size = size;
	*first = dest;
	return (dest);
}

void	free_allocs(t_alloc *first)
{
	t_alloc	*to_remove;

	while (first)
	{
		to_remove = first;
		first = to_remove->next;
		free(to_remove->ptr);
		free(to_remove);
	}
}
