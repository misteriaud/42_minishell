/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/28 17:46:54 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_err	feed_quote(t_ctx *ctx, t_token *token, char *str, int *i)
{
	t_str	in_quotes;
	char	quote;

	in_quotes.len = 0;
	in_quotes.str = NULL;
	if (str[*i] != '\'' && str[*i] != '\"')
		return (NO_ERROR);
	quote = str[*i];
	while (str[++*i] != quote)
	{
		if (xrealloc(&in_quotes.str, in_quotes.len + 2, PARS_ALLOC))
			return (MEMORY_ERROR);
		in_quotes.str[in_quotes.len] = str[*i];
		in_quotes.len++;
	}
	if (!str[++*i])
		return (PARSING_ERROR);
	if (quote == '\"' && drop_variables(ctx, &in_quotes))
		return (PARSING_ERROR);

	return (NO_ERROR);
}

t_err	feed_token(t_ctx *ctx, t_token *token, char *str, int *i)
{
	(void)ctx;
	if (str[*i] == str[*i + 1] && (str[*i] == '<' || str[*i] == '>'))
	{
		token->type += 64;
		*i += 2;
	}
	else if (str[*i] == '<' || str[*i] == '>')
		(*i)++;
	while (str[*i] == ' ')
		(*i)++;
	while (str[*i] && str[*i] != '<' && str[*i] != '>' && (!token->value.str || str[*i] != ' '))
	{
		if (feed_quote(ctx, token, str, i))
			return (PARSING_ERROR);
		if (xrealloc(&token->value.str, token->value.len + 2, PARS_ALLOC))
			return (MEMORY_ERROR);
		token->value.str[token->value.len] = str[*i];
		token->value.len++;
		(*i)++;
	}
	if (!token->value.str)
		return (PARSING_ERROR);
	return (NO_ERROR);
}

t_err	split_by_chev(t_ctx *ctx, t_token *first)
{
	int		i;
	t_token	*curr;
	t_err	err;
	char	*str;

	(void)ctx;
	i = -1;
	err = NO_ERROR;
	curr = first;
	str = first->value.str;
	first->value = (t_str){NULL, 0};
	while (!err && str[++i])
	{
		if ((str[i] == '<' || str[i] == '>') && !new_branch(&curr, str[i]))
			err = feed_token(ctx, curr, str, &i);
		else
		{
			if (xrealloc(&first->value.str, first->value.len + 2, PARS_ALLOC))
				return (MEMORY_ERROR);
			first->value.str[first->value.len] = str[i];
			first->value.len++;
		}
	}
	xfree(str, PARS_ALLOC);
	return (NO_ERROR);
}

t_err	split_by_pipe(t_ctx *ctx, t_token *first, char *str)
{
	int		i;
	t_token	*curr;

	(void)ctx;
	i = 0;
	curr = first;
	while (str[i])
	{
		if (str[i] == '|' && new_branch(&curr, '|'))
			return (MEMORY_ERROR);
		else if (xrealloc(&curr->value.str, curr->value.len + 2, PARS_ALLOC))
			return (MEMORY_ERROR);
		else
		{
			curr->value.str[curr->value.len] = str[i];
			curr->value.len++;
		}
		i++;
	}
	return (NO_ERROR);
}

t_err	parse(t_ctx *ctx, char *str)
{
	t_err	err;
	t_token	*curr;

	err = NO_ERROR;
	if (xmalloc(&ctx->parse_tree, sizeof(*ctx->parse_tree), PARS_ALLOC))
		return (MEMORY_ERROR);
	ctx->parse_tree->type = CMD;
	err = split_by_pipe(ctx, ctx->parse_tree, str);
	curr = ctx->parse_tree;
	while (!err && curr)
		err = split_by_chev(ctx, curr);


	return (err);
}
