#ifndef ENV_H
# define ENV_H

# include <struct.h>

#define ENV_GROUP	0

int		init_env(t_ctx *ctx, char **env);
int		print_env(t_ctx *ctx);
int		export_env(t_ctx *ctx, const char *str);

#endif
