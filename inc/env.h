#ifndef ENV_H
# define ENV_H

# include <struct.h>

#define ENV_GROUP	0

t_err	init_env(t_ctx *ctx, char **env);

t_err	print_env(t_ctx *ctx);

t_err	refresh_paths(t_ctx *ctx);

// get value of variable
t_err	get_variable(t_ctx *ctx, const char *key, t_str *value);

// test and get execution path
t_err	get_exec_path(t_ctx *ctx, t_str *exec);

// replace variable key by value in string
t_err	drop_variables(t_ctx *ctx, t_str *parse);

// duplicate variable environment list to array
t_err	package_env(t_ctx *ctx);

#endif
