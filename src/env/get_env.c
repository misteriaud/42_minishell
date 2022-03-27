/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:14:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 18:15:58 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	get_env(t_ctx *ctx, const char *key, char **value)
{
	t_env	*elm;

	elm = ctx->env;
	while (elm)
	{
		if (!compare(key, elm->key.str))
		{
			*value = elm->value.str;
			return (NO_ERROR);
		}
		elm = elm->next;
	}
	return (NO_VAR_ERROR);
}
