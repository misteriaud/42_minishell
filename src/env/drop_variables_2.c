/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop_variables_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:08:36 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 16:10:15 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <status.h>

int	check_interrogation(t_ctx *ctx, char **str, t_str *tmp)
{
	char	*num;

	if (**str == '?')
	{
		num = ft_itoa(ctx->old_status);
		tmp->len = get_len(num);
		if (new_str(tmp, tmp->len, TMP_ALLOC))
			return (MEMORY_ERROR);
		str_fill(tmp, num);
		(*str)++;
		xfree(num, ENV_ALLOC);
		return (1);
	}
	return (0);
}

t_err	create_var_node(t_ctx *ctx, char **str,
		t_lst ***elm, int *global_len)
{
	t_str	tmp;

	tmp.len = 0;
	if (!check_interrogation(ctx, str, &tmp))
	{
		while (is_variable((*str)[tmp.len]))
			tmp.len++;
		if (new_str(&tmp, tmp.len, TMP_ALLOC))
			return (MEMORY_ERROR);
		str_fill(&tmp, *str);
		(*str) += tmp.len;
		if (get_variable(ctx, tmp.str, &tmp))
			return (NO_ERROR);
	}
	return (alloc_node(elm, global_len, &tmp));
}

t_err	create_text_node(char **str, t_lst ***elm,
		int *global_len, const char sep)
{
	t_str	tmp;

	tmp.len = 0;
	if (byte_count(*str, &(tmp.len), sep))
		return (NO_ERROR);
	if (new_str(&tmp, tmp.len, TMP_ALLOC))
		return (MEMORY_ERROR);
	str_fill(&tmp, *str);
	(*str) += tmp.len;
	return (alloc_node(elm, global_len, &tmp));
}

t_err	create_dollar_node(t_lst ***elm, int *global_len)
{
	t_str	tmp;

	if (new_str(&tmp, 1, TMP_ALLOC))
		return (MEMORY_ERROR);
	*tmp.str = '$';
	tmp.len = 1;
	return (alloc_node(elm, global_len, &tmp));
}
