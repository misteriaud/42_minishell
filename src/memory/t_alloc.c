/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_alloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:31:02 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/25 16:44:26 by artblin          ###   ########.fr       */
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

void	xfree(void *ptr, int group)
{
	t_alloc		**first;
	t_alloc	*curr;
	t_alloc	*to_remove;
	first = get_first_alloc(group);

	if (!first)
		return ;
	if (*first && (*first)->ptr == ptr && !(*first)->next)
	{
		xfree_group(group); return ;
	}
	else if (*first && (*first)->ptr == ptr)
	{
		to_remove = *first;
		*first = to_remove->next;
		free(to_remove->ptr);
		free(to_remove);
	}
	curr = *first;
	while (curr && curr->next && curr->next->ptr != ptr)
		curr = curr->next;
	if (!curr || !curr->next || curr->next->ptr != ptr)
		return ;
	to_remove = curr->next;
	free(to_remove->ptr);
	curr->next = to_remove->next;
	free(to_remove);
}

void	xfree_allocs(t_alloc *first)
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
