/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:06:59 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 18:15:57 by artblin          ###   ########.fr       */
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
	return (NO_ERROR);
}
