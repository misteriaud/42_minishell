/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:06:59 by artblin           #+#    #+#             */
/*   Updated: 2022/05/06 15:59:27 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_err	byte_copy(t_str *new, char **str, const char end)
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

t_err	add_to_env2(t_ctx *ctx, char *key, char *value)
{
	t_env	**elm;

	elm = &ctx->env;
	while (*elm)
		elm = &(*elm)->next;
	if (xmalloc(elm, sizeof(t_env), ENV_ALLOC))
		return (MEMORY_ERROR);
	(*elm)->key.str = key;
	(*elm)->key.len = get_len(key);
	(*elm)->value.str = value;
	(*elm)->value.len = get_len(value);
	return (NO_ERROR);
}

void	no_env(t_ctx *ctx)
{
	char	*key;
	char	*value;
	t_str	*shlvl;
	int		n;

	if (get_variable(ctx, "PWD", NULL))
	{
		value = getcwd(NULL, 0);
		str_dup(&key, "PWD", ENV_ALLOC);
		add_to_env2(ctx, key, value);
	}
	if (get_variable(ctx, "SHLVL", NULL))
	{
		str_dup(&key, "SHLVL", ENV_ALLOC);
		str_dup(&value, "1", ENV_ALLOC);
		add_to_env2(ctx, key, value);
	}
	else
	{
		get_address_variable(ctx, "SHLVL", &shlvl);
		secure_atoi(shlvl->str, &n);
		n++;
		value = ft_itoa(n);
		xfree(shlvl->str, ENV_ALLOC);
		shlvl->str = value;
		shlvl->len = get_len(value);
	}
}


t_err	init_env(t_ctx *ctx, char **env)
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
	no_env(ctx);
	return (NO_ERROR);
}
