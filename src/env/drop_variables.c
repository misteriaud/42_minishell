/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drop_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 22:25:36 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 16:15:04 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <status.h>

t_err	alloc_node(t_lst ***elm, int *global_len, t_str *tmp)
{
	if (xmalloc(*elm, sizeof(t_lst), TMP_ALLOC))
		return (MEMORY_ERROR);
	(**elm)->data = *tmp;
	*global_len += tmp->len;
	*elm = &((**elm)->next);
	return (NO_ERROR);
}

static void	fill(t_str *parse, t_lst *lst)
{
	xfree(parse->str, PARS_ALLOC);
	if (!lst)
	{
		parse->len = 0;
		parse->str = NULL;
		return ;
	}
	new_str(parse, parse->len, PARS_ALLOC);
	str_fill_from_lst(parse, lst);
	xfree_group(TMP_ALLOC);
}

static t_err	drop(t_ctx *ctx, t_str *parse)
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
				err = create_var_node(ctx, &str, &elm, &(parse->len));
			else if (!*str || is_white(*str) || *str == '+' || *str == '=')
				err = create_dollar_node(&elm, &(parse->len));
			else
				++str;
		}
	}
	return (fill(parse, lst), err);
}

t_err	drop_variables(t_ctx *ctx, t_str *parse)
{
	if (!parse | !parse->str | !*parse->str)
		return (NO_ERROR);
	return (drop(ctx, parse));
}
