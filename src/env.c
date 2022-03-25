#include <minishell.h>

#define NO_ENV_ERROR	12
#define MEMORY_ERROR	1

int	get_env()
{
	return (0);
}

int	add_env_var(t_env **head, const char *key, const char *value)
{
	t_env	*new;

	if (xmalloc(&new, sizeof(t_env), ENV_GROUP))
		return (MEMORY_ERROR);
	new->key = key;
	new->value = value;
	new->next = *head;
	*head = new;
	return (SUCCESS);
}

int	init_env(t_ctx *ctx, char **env)
{
	if (!env)
		return (NO_ENV_ERROR);
	while (env)
	{
		add_env_var(&ctx->head_history);
		env++;
	}

	return (0);
}

