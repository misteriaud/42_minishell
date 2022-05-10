/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:05:17 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 16:45:52 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_total_env_size(t_env *elm, int *size)
{
	*size = 0;
	while (elm)
	{
		printf("%d %s\n", elm->key.len, elm->key.str);
		printf("%d %s\n", elm->value.len, elm->value.str);
		*size += (elm->key.len + elm->value.len + 2);
		elm = elm->next;
	}
	if (*size)
		return (NO_ERROR);
	return (NO_ENV_ERROR);
}

static void	copy_env(char *dest, t_env *elm)
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

t_err	print_env(t_ctx *ctx)
{
	t_env	*elm;
	char	*env;
	int		size;

	elm = ctx->env;
	if (get_total_env_size(elm, &size))
		return (NO_ENV_ERROR);
	if (xmalloc(&env, size, ENV_ALLOC))
		return (MEMORY_ERROR);
	copy_env(env, elm);
	xfree(env, ENV_ALLOC);
	return (NO_ERROR);
}
