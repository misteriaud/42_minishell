/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:25:36 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 17:00:46 by artblin          ###   ########.fr       */
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

static t_err	create_variable_node(t_ctx *ctx, char **str,
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
	if (xmalloc(*elm, sizeof(t_lst), TMP_ALLOC))
		return (MEMORY_ERROR);
	(**elm)->data = tmp;
	*global_len += tmp.len;
	*elm = &((**elm)->next);
	return (NO_ERROR);
}

static t_err	create_text_node(char **str, t_lst ***elm,
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
	if (xmalloc(*elm, sizeof(t_lst), TMP_ALLOC))
		return (MEMORY_ERROR);
	(**elm)->data = tmp;
	*global_len += tmp.len;
	*elm = &((**elm)->next);
	return (NO_ERROR);
}

static void	fill(t_str *parse, t_lst *lst)
{
	xfree(parse->str, PARS_ALLOC);
	new_str(parse, parse->len, PARS_ALLOC);
	str_fill_from_lst(parse, lst);
	xfree_group(TMP_ALLOC);
}

t_err	drop_variables(t_ctx *ctx, t_str *parse)
{
	t_lst		**elm;
	t_lst		*lst;
	char		*str;
	t_err		err;

	lst = NULL;
	elm = &lst;
	str = parse->str;
	parse->len = 0;
	err = NO_ERROR;
	while (!err && *str)
	{
		if (!err && *str != '$')
			err = create_text_node(&str, &elm, &(parse->len), '$');
		if (!err && *str == '$')
		{
			if (is_var_start(*++(str)) || *str == '?')
				err = create_variable_node(ctx, &str, &elm, &(parse->len));
			else
				err = create_text_node(&str, &elm, &(parse->len), '\0');
		}
	}
	fill(parse, lst);
	return (err);
}
