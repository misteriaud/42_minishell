/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:10:44 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/11 11:31:35 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <struct.h>
# include <env.h>
# include <built_in.h>
# include <utils.h>
# include <memory.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <sys/ioctl.h>
# include <status.h>

typedef struct s_wstatus
{
	int		pid;
	int		status;
}	t_wstatus;

t_err	redirect_in(t_token *in, t_err *err, int *dfd);
t_err	redirect_out(t_token *path, t_err *err, int *dfd);

t_err	run_process(t_ctx *ctx);
t_err	execute(t_ctx *ctx, t_token *token, int *dfd);

t_err	get_exit_status(void);

#endif
