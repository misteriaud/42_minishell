/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:58:07 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/19 16:26:55 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static t_err	split_cmd2(t_token *curr)
{
	char	**split;
	t_token	*new;
	int		i;

	split = NULL;
	i = 0;
	if (split_arr(&split, curr->value.str, ' ', PARS_ALLOC))
		return (MEMORY_ERROR);
	while (split[++i])
	{
		if (xmalloc(&new, sizeof(*new), PARS_ALLOC))
			return (MEMORY_ERROR);
		new->next = curr->arg;
		new->value.str = split[i];
		new->value.len = get_len(split[i]);
		curr->arg = new;
	}
	curr->value.str = split[0];
	curr->value.len = get_len(split[0]);
	return (NO_ERROR);
}

t_err	split_cmd(t_token *curr)
{
	while (curr)
	{
		if (!is_only_set(curr->value.str, " ")
			&& is_containing_set(curr->value.str, " ") && split_cmd2(curr))
			return (MEMORY_ERROR);
		curr = curr->out;
	}
	return (NO_ERROR);
}
