/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 02:12:00 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 15:33:25 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN
# define BUILT_IN

# include <struct.h>

#define CMD_CD			0
#define CMD_PWD			1
#define CMD_ENV			2
#define CMD_EXIT		3
#define CMD_ECHO		4
#define CMD_UNSET		5
#define CMD_EXPORT		6


#define BUILT_IN_NBR	7
#define BUILT_ALLOC		112


t_err	init_built_in(t_ctx *ctx);

t_func	*search_built_in(t_ctx *ctx, const char *exec);

void	cmd_cd(t_ctx *ctx, t_token *args);

void	cmd_env(t_ctx *ctx, t_token *args);

void	cmd_echo(t_ctx *ctx, t_token *args);

void	cmd_exit(t_ctx *ctx, t_token *args);

void	cmd_export(t_ctx *ctx, t_token *args);

void	cmd_pwd(t_ctx *ctx, t_token *args);

void	cmd_unset(t_ctx *ctx, t_token *args);
#endif
