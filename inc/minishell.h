/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:43 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/25 17:57:44 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_str
{
	char	*str;
	int		len;
}	t_str;

typedef struct s_ctx
{
	int		fd_history;
	t_str	*head_history;
}	t_ctx;

#endif
