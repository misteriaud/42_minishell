/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:50 by artblin           #+#    #+#             */
/*   Updated: 2022/05/04 15:50:19 by artblin          ###   ########.fr       */
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
	while(is_variable(*str[size]))
		size++;
	if (!size && xmalloc(&key, sizeof(char) * (i + 1)))
		return (NULL);
	while (x < size)
	{

	}
}


char	*get_value(char **str)
{


}

int	check_assignement(char **str)
{

	return (NO_ASSIGNEMENT);
}

t_err	add_to_env(t_ctx *ctx, char *key, char *value)
{


}


t_err	cmd_export(t_ctx *ctx, t_token *args)
{
	char	*str;
	char	*key;
	char	*value;
	int		assign;

	if (args && args->value.str)
	{
		str = args->value.str;

		key = get_key(&str);
		assign = check_assignement(&str);
		value = get_value(&str);

		if (key && value && (assign == ADD || assign == CREATE))
		{
			add_to_env(ctx, key, value);
			return (NO_ERROR);
		}
	}
	return (ERROR);
}
