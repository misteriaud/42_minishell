#include <minishell.h>

#define NO_ENV_ERROR	12
#define MEMORY_ERROR	1
#define NO_ERROR		0


/*
int	export_env(t_ctx *ctx, const char *str)
{
	(void)ctx;
	t_env	*new;
	int		state;

	state = 0;
	if (xmalloc(&new, sizeof(t_env), ENV_ALLOC))
		return (MEMORY_ERROR);
	while (str[new->key.len])
	{
		if (str[new->key.len] == '=')
		{
			state++;
			break ;
		}
		new->key.len++;
	}
	printf("len -> %d\n", new->key.len);
	return (NO_ERROR);
}*/

int	get_env_size(t_env *elm)
{
	int		size;

	size = 0;
	while (elm)
	{
		size += (elm->key.len + elm->value.len + 2);
		elm = elm->next;
	}
	return (size);
}

void	copy_env(char *dest, t_env *elm)
{
	int		x;

	while (elm)
	{
		x = 0;
		while (elm->key.str[x])
			*(dest)++ = elm->key.str[x++];
		*(dest)++ = '=';
		x = 0;
		while (elm->value.str[x])
			*(dest)++ = elm->value.str[x++];
		*(dest)++ = '\n';
		elm = elm->next;
	}
}

int	print_env(t_ctx *ctx)
{
	t_env	*elm;
	char	*env;
	int		size;

	elm = ctx->env;
	size = get_env_size(elm);
	if (xmalloc(&env, size, ENV_ALLOC))
		return (MEMORY_ERROR);
	copy_env(env, elm);
	write(1, env, size);
	xfree(env, ENV_ALLOC);
	return (NO_ERROR);
}

int	byte_copy(t_str *new, char **str, const char end)
{
	int		x;

	new->len = 0;
	while ((*str)[new->len] != end)
		new->len++;
	if (xmalloc(&(new->str), new->len + 1, ENV_ALLOC))
		return (MEMORY_ERROR);
	(new->str)[new->len] = '\0';
	x = 0;
	while (**str != end)
		(new->str)[x++] = *(*str)++;
	++(*str);
	return (NO_ERROR);
}

int	init_env(t_ctx *ctx, char **env)
{
	t_env	**elm;

	elm = &ctx->env;
	if (!env)
		return (NO_ENV_ERROR);
	while (*env)
	{
		if (xmalloc(elm, sizeof(t_env), ENV_ALLOC)
			| byte_copy(&(*elm)->key, env, '=')
			| byte_copy(&(*elm)->value, env, '\0'))
			return (MEMORY_ERROR);
		elm = &(*elm)->next;
		env++;
	}
	return (NO_ERROR);
}
