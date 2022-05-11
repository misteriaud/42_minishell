/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:07:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/10 15:42:28 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory.h>
#include <readline/history.h>
#include <readline/readline.h>

// int	*curr_group(void)
// {
// 	static int	group = 0;
// 
// 	return (&group);
// }

int	xmalloc(void *ptr, size_t size, int group)
{
	t_alloc	**first;
	t_alloc	*dest;
	void	**data;

	data = (void **)ptr;
	first = get_first_alloc(group);
	dest = new_alloc(first, size);
	if (!dest)
		return (1);
	ft_bzero(dest->ptr, size);
	*data = dest->ptr;
	return (0);
}

int	xrealloc(void *ptr, size_t size, int group)
{
	t_alloc	**first;
	t_alloc	*curr;
	void	*dest;
	void	**data;

	data = (void **)ptr;
	if (!*data)
		return (xmalloc(ptr, size, group));
	first = get_first_alloc(group);
	curr = *first;
	while (curr && curr->ptr != *data)
		curr = curr->next;
	if (!curr)
		return (xmalloc(ptr, size, group));
	dest = malloc(size);
	if (!dest)
		return (1);
	ft_memcpy(dest, curr->ptr, curr->size);
	ft_bzero((char *)dest + curr->size, size - curr->size);
	free(curr->ptr);
	curr->ptr = dest;
	curr->size = size;
	*data = curr->ptr;
	return (0);
}

void	xfree(void *ptr, int group)
{
	t_alloc		**first;
	t_alloc		*prev;
	t_alloc		*curr;

	prev = NULL;
	first = get_first_alloc(group);
	if (!first)
		return ;
	curr = *first;
	while (curr && curr->ptr != ptr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev && curr && !curr->next)
		xfree_group(group);
	if (!curr || !curr->next)
		return ;
	if (!prev)
		*first = curr->next;
	else
		prev->next = curr->next;
	free(curr->ptr);
	free(curr);
}

void	xfree_group(int group)
{
	t_node	**first;
	t_node	*curr;
	t_node	*to_remove;

	first = get_first_node();
	if (*first && (*first)->group == group)
	{
		to_remove = *first;
		*first = to_remove->next;
		free_allocs(to_remove->first);
		free(to_remove);
		return ;
	}
	curr = *first;
	while (curr && curr->next && curr->next->group != group)
		curr = curr->next;
	if (!curr || (curr && !curr->next))
		return ;
	to_remove = curr->next;
	curr->next = to_remove->next;
	free_allocs(to_remove->first);
	free(to_remove);
}

void	xfree_all(void)
{
	t_node	**first;
	t_node	*to_remove;

	first = get_first_node();
	if (!*first)
		return ;
	while (*first)
	{
		to_remove = *first;
		*first = to_remove->next;
		free_allocs(to_remove->first);
		free(to_remove);
	}
	rl_clear_history();
}
