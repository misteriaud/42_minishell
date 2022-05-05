#ifndef PROCESS_H
# define PROCESS_H

#include <struct.h>
# include <env.h>
# include <built_in.h>
#include <utils.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <sys/ioctl.h>

t_err	redirect_in(t_token *in, t_err *err);
t_err	redirect_out(t_token *path, t_err *err);

t_err	run_process(t_ctx *ctx);
t_err	execute(t_ctx *ctx, t_token *token);
#endif
