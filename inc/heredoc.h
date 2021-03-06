/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:25:26 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/19 15:32:07 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include <struct.h>
# include <memory.h>
# include <env.h>
# include <utils.h>

# include <stdio.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

void	unlink_heredoc(t_token *curr);
t_err	get_tmp_path(int *fd, char **path);
t_err	readline_to_mem(t_str *line);
t_err	prompt_heredoc(t_ctx *ctx);

#endif
