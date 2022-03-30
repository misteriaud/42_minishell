#ifndef PROCESS_H
# define PROCESS_H

#include <struct.h>
# include <env.h>
# include <built_in.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


t_err	run_process(t_ctx *ctx);
t_err	execute(t_ctx *ctx, t_token *token, t_err *err);
#endif
