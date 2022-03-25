#ifndef ENV_H
# define ENV_H

#define ENV_GROUP	0

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		init_env(t_ctx *ctx, char **env);

#endif
