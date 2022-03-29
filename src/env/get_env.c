/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:14:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 16:54:02 by artblin          ###   ########.fr       */
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

t_err	extract_var(char **str, t_str *out)
{
	int		byte;
	int		x;

	byte = 0;
	while (is_variable((*str)[byte]))
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

	byte = 0;
	byte_count(*str, &byte, '$');
	if (new_str(out, byte, TMP_ALLOC))
		return (MEMORY_ERROR);
	str_fill(out, *str);
	(*str) += byte;
	return (NO_ERROR);
}

t_err	replace_var(t_ctx *ctx, t_str *parse)
{
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
		printf("*str->%c\n", *str);
		if (*str != '$')
		{
			extract_text(&str, &text);
			if (xmalloc(elm, sizeof(t_lst), TMP_ALLOC))
				return (MEMORY_ERROR);
			(*elm)->data = text;
			byte += text.len;
			//printf("str// byte::%d str::%s\n", byte, (*elm)->data.str);
			elm = &((*elm)->next);
		}
		if (*str == '$')
		{
			str++;
			extract_var(&str, &var);
			if (get_env(ctx, var.str, &var))
				continue ;
			if (xmalloc(elm, sizeof(t_lst), TMP_ALLOC))
				return (MEMORY_ERROR);
			(*elm)->data = var;
			byte += var.len;
			//printf("var// byte::%d str::%s\n", byte, (*elm)->data.str);
			elm = &((*elm)->next);
		}
	}
	//printf("byte::%d\n", byte);
	xfree(parse->str, PARS_ALLOC);
	new_str(parse, byte, PARS_ALLOC);
	while (lst)
	{
		while (*(lst->data.str))
			parse->str[x++] = *(lst->data.str)++;
		lst = lst->next;
	}
	return (NO_ERROR);
}
