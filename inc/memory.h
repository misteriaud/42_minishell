/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:14 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/28 17:43:46 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stdlib.h>

typedef struct s_alloc {
	void			*ptr;
	size_t			size;
	struct s_alloc	*next;
}				t_alloc;

typedef struct s_node {
	int				group;
	t_alloc			*first;
	struct s_node	*next;
}				t_node;

// INTERNALS FUNCTIONS
void	ft_bzero(void *s, size_t n);
void	ft_memcpy(void *dest, const void *src, size_t n);
t_node	**get_first_node(void);
t_node	*new_node(t_node **first, int group);
t_node	*get_node(int group);
t_alloc	**get_first_alloc(int group);
t_alloc	*new_alloc(t_alloc **first, size_t size);
void	free_allocs(t_alloc *first);

// libmemory.c
int 	*curr_group(void);
int		xmalloc(void *ptr, size_t size, int group);
int		xrealloc(void *ptr, size_t size, int group);
void	xfree(void *ptr, int group);
void	xfree_group(int group);
void	xfree_all(void);

#endif
