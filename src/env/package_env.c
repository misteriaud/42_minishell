/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   package_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:38:44 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 14:07:25 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	str_fill_sep(char *out, const char *in, const char sep)
{
	if (!out | !in)
		return (NULL_PTR_ERROR);
	while (*in && *in != sep)
		*(out)++ = *(in)++;
	return (NO_ERROR);
}

int		get_env_len(const t_env *elm)
{
	int		size;

	size = 0;
	while (elm)
	{
		size++;
		elm = elm->next;
	}
	return (size);
}

t_err	package_env(t_ctx *ctx)
{
	t_env	*elm;
	int		z;

	if (xmalloc(&(ctx->exec_env),
		(get_env_len(ctx->env) + 1) * sizeof(char *), EXEC_ALLOC))
		return (MEMORY_ERROR);
	elm = ctx->env;
	z = 0;
	while (elm)
	{
		if (xmalloc(&(ctx->exec_env[z]),
			(elm->key.len + elm->value.len + 2), EXEC_ALLOC))
			return (MEMORY_ERROR);
		str_fill_sep(ctx->exec_env[z],
			elm->key.str, '=');
		ctx->exec_env[z][elm->key.len] = '=';
		str_fill_sep(&(ctx->exec_env[z][elm->key.len + 1]),
			elm->value.str, '\0');
		z++;
		elm = elm->next;
	}
	return (NO_ERROR);
}
