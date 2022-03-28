#ifndef ENV_H
# define ENV_H

# include <struct.h>

#define ENV_GROUP	0

t_err	init_env(t_ctx *ctx, char **env);
t_err	print_env(t_ctx *ctx);
t_err	get_env(t_ctx *ctx, const char *key, t_str *value);
t_err	refresh_paths(t_ctx *ctx);
t_err	get_exec_path(t_ctx *ctx, t_str *exec);

#endif
