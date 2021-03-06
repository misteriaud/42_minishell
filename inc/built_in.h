/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:12:00 by artblin           #+#    #+#             */
/*   Updated: 2022/05/11 09:34:04 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include <struct.h>
# include <memory.h>
# include <utils.h>
# include <env.h>

# define ADD				1
# define CREATE			2
# define NO_ASSIGNEMENT	3

# define CMD_CD			0
# define CMD_PWD			1
# define CMD_ENV			2
# define CMD_EXIT		3
# define CMD_ECHO		4
# define CMD_UNSET		5
# define CMD_EXPORT		6

# define BUILT_IN_NBR	7
# define BUILT_ALLOC		112

t_err	init_built_in(t_ctx *ctx);
t_func	*search_built_in(t_ctx *ctx, const char *exec);

t_err	cmd_cd(t_ctx *ctx, t_token *args);
t_err	cmd_env(t_ctx *ctx, t_token *args);
t_err	cmd_echo(t_ctx *ctx, t_token *args);
t_err	cmd_exit(t_ctx *ctx, t_token *args);
t_err	cmd_export(t_ctx *ctx, t_token *args);
t_err	cmd_pwd(t_ctx *ctx, t_token *args);
t_err	cmd_unset(t_ctx *ctx, t_token *args);

char	*get_key(char **str);
#endif
