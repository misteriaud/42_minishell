/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:14:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 15:47:28 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	get_env(t_ctx *ctx, const char *key, t_str *value)
{
	t_env	*elm;

	elm = ctx->env;
	while (elm)
	{
		if (!compare(key, elm->key.str))
		{
			value->str = elm->value.str;
			value->len = elm->value.len;
			return (NO_ERROR);
		}
		elm = elm->next;
	}
	return (NO_VAR_ERROR);
}

int	is_num(const char c)
{
	return ((c >= '0') & (c <= '9'));
}

int is_lower(const char c)
{
	return ((c >= 'a') & (c <= 'z'));
}

int is_upper(const char c)
{
	return ((c >= 'A') & (c <= 'Z'));
}
int is_under(const char c)
{
	return (c == '_');
}

int	is_var(const char c)
{
	return (is_num(c) | is_lower(c) | is_upper(c) | is_under(c));
}

t_err	extract_var(char **str, t_str *out)
{
	int		byte;
	int		x;

	(*str)++;
	byte = 0;
	while (is_var((*str)[byte]))
		byte++;
	if (xmalloc(&(out->str), byte + 1, TMP_ALLOC))
		return (MEMORY_ERROR);
	x = 0;
	while (x < byte)
	{
		out->str[x] = (*str)[x];
		x++;
	}
	out->len = byte;
	(*str) += byte;
	return (NO_ERROR);
}

t_err	extract_text(char **str, t_str *out)
{
	int		byte;
	int		x;

	byte = 0;
	while ((*str)[byte] != '$')
		byte++;
	if (xmalloc(&(out->str), byte + 1, TMP_ALLOC))
		return (MEMORY_ERROR);
	x = 0;
	while (x < byte)
	{
		out->str[x] = (*str)[x];
		x++;
	}
	out->len = byte;
	(*str) += byte;
	return (NO_ERROR);
}

t_err	replace_var(t_ctx *ctx, t_str *parse)
{
	(void)ctx;
	char		*str;
	t_str		var;
	t_str		text;
	t_lst		*lst;
	t_lst		**elm;
	int			byte;
	int			x;

	x = 0;

	byte = 0;
	lst = NULL;
	elm = &lst;
	str = parse->str;
	while (*str)
	{
		if (*str != '$')
		{
			extract_text(&str, &text);
			if (xmalloc(elm, sizeof(t_lst), TMP_ALLOC))
				return (MEMORY_ERROR);
			(*elm)->data = text;
			elm = &((*elm)->next);
			byte += text.len;
		}
		if (*str == '$')
		{
			extract_var(&str, &var);
			if (get_env(ctx, var.str, &var))
				continue ;
			if (xmalloc(elm, sizeof(t_lst), TMP_ALLOC))
				return (MEMORY_ERROR);
			(*elm)->data = var;
			elm = &((*elm)->next);
			byte += var.len;
		}
	}
	if (xmalloc(&(parse->str), byte + 1, PARS_ALLOC))
		return (MEMORY_ERROR);
	while (lst)
	{
		while (*(lst->data.str))
			parse->str[x++] = *(lst->data.str)++;
		//write(1, lst->data.str, lst->data.len);
		//write(1, "\n", 1);
		lst = lst->next;
	}
	return (NO_ERROR);
}
