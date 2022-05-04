/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:50 by artblin           #+#    #+#             */
/*   Updated: 2022/05/04 19:30:57 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define ADD				1
#define CREATE			2
#define NO_ASSIGNEMENT	3


char	*get_key(char **str)
{
	int		x;
	int		size;
	char	*key;

	if (!is_var_start(**str))
		return (NULL);
	size = 0;
	while(is_variable((*str)[size]))
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
	(void)str;
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

t_err	add_to_env(t_ctx *ctx, char *key, char *value)
{
	(void)ctx;
	(void)key;
	(void)value;
	return (NO_ERROR);
}


t_err	cmd_export(t_ctx *ctx, t_token *args)
{
	char	*str;
	char	*key;
	char	*value;
	int		assign;

	(void)value;
	(void)assign;
	(void)ctx;
	if (args && args->value.str)
	{
		str = args->value.str;
		key = get_key(&str);
		assign = check_assignement(&str);
		value = get_key(&str);
		if (key && value && (assign == ADD || assign == CREATE))
		{
			add_to_env(ctx, key, value);
			printf("key --> %s\n", key);
			printf("value --> %s\n", value);
			return (NO_ERROR);
		}
	}
	return (NO_ERROR);
}
