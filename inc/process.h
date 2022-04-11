#ifndef PROCESS_H
# define PROCESS_H

#include <struct.h>
# include <env.h>
# include <built_in.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

t_err	run_process(t_ctx *ctx);
void	execute(t_ctx *ctx, t_token *token);
#endif
