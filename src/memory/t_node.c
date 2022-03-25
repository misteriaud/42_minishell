/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_node.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:30:25 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/25 17:10:15 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory.h>

t_node	**get_first_node(void)
{
	static t_node	*first;

	return (&first);
}

t_node	*new_node(t_node **first, int group)
{
	t_node	*dest;

	dest = malloc(sizeof(*dest));
	if (!dest)
		return (NULL);
	dest->next = *first;
	dest->group = group;
	dest->first = NULL;
	*first = dest;
	return (dest);
}

t_node	*get_node(int group)
{
	t_node	**first;
	t_node	*curr;

	first = get_first_node();
	curr = *first;
	while (curr)
	{
		if (curr->group == group)
			return (curr);
		curr = curr->next;
	}
	return (new_node(first, group));
}
