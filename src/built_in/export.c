/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:50 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 16:36:23 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

char	*get_key(char **str)
{
	int		x;
	int		size;
	char	*key;

	if (!is_var_start(**str))
		return (NULL);
	size = 0;
	while (is_variable((*str)[size]))
		size++;
	if (size && !xmalloc(&key, sizeof(char) * (size + 1), ENV_ALLOC))
	{
		x = 0;
		while (x < size)
			key[x++] = *(*str)++;
		return (key);
	}
	return (NULL);
}

char	*get_value(char **str)
{
	int		x;
	int		size;
	char	*value;

	size = 0;
	while ((*str)[size])
		size++;
	if (size && !xmalloc(&value, sizeof(char) * (size + 1), ENV_ALLOC))
	{
		x = 0;
		while (x < size)
			value[x++] = *(*str)++;
		return (value);
	}
	return (NULL);
}

int	check_assignement(char **str)
{
	if ((*str)[0] == '=')
		return ((*str)++, CREATE);
	else if ((*str)[0] == '+' && (*str)[1] == '=')
		return ((*str) += 2, ADD);
	return (NO_ASSIGNEMENT);
}

t_err	add_to_env(t_ctx *ctx, char *key, int assign, char *value)
{
	t_env	**elm;
	t_str	*target;
	char	*merge;

	elm = &ctx->env;
	if (!get_address_variable(ctx, key, &target))
	{
		merge = value;
		if (assign == ADD)
			merge = str_join(target->str, value, ENV_ALLOC);
		xfree(target->str, ENV_ALLOC);
		target->str = merge;
		target->len = get_len(merge);
		return (NO_ERROR);
	}
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

t_err	cmd_export(t_ctx *ctx, t_token *args)
{
	char	*str;
	char	*key;
	char	*value;
	int		assign;
	t_err	err;

	err = NO_ERROR;
	if (!args)
		return (err);
	while (args)
	{
		if (args->value.str)
		{
			str = args->value.str;
			key = get_key(&str);
			assign = check_assignement(&str);
			value = get_value(&str);
			if (!key || !(assign == ADD || assign == CREATE))
				err = print_err(EXPORT_ERROR, args->value.str);
			add_to_env(ctx, key, assign, value);
		}
		args = args->next;
	}
	return (!!err);
}
