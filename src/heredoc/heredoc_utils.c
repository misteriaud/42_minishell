/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:59:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/18 11:01:15 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

t_err	get_tmp_path(int *fd, char **path)
{
	static unsigned int	id;

	*path = NULL;
	*path = str_join("/tmp/minishell", ft_itoa(id), EXEC_ALLOC);
	if (!path)
		return (MEMORY_ERROR);
	while (is_reg(*path))
	{
		id++;
		*path = str_join("/tmp/minishell", ft_itoa(id), EXEC_ALLOC);
		if (!path)
			return (MEMORY_ERROR);
	}
	*fd = open(*path, O_RDWR | O_CREAT | O_TRUNC, 777);
	return (NO_ERROR);
}

void	unlink_heredoc(t_token *curr)
{
	t_token	*curr_in;

	while (curr)
	{
		curr_in = curr->in;
		while (curr_in)
		{
			if (curr_in->type == HEREDOC)
				unlink(curr_in->value.str);
			curr_in = curr_in->next;
		}
		curr = curr->out;
	}
}
