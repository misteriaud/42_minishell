#ifndef ENV_H
# define ENV_H

# include <struct.h>

#define ENV_GROUP	0

t_err	init_env(t_ctx *ctx, char **env);
t_err	print_env(t_ctx *ctx);
t_err	get_env(t_ctx *ctx, const char *key, char **value);

#endif
