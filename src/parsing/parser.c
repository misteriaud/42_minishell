/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/28 13:59:08 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_err	split_by_chev(t_ctx *ctx, t_token *first, char *str)
{
	int		i;
	t_token	*curr;
	char	metachar;

	(void)ctx;
	i = -1;
	metachar = 0;
	curr = first;
	while (str[++i])
	{
		if (str[i] == ' ')
			continue ;
		if (str[i] == '<')
		{
			metachar = str[i];
			curr = add_token_back(curr, &curr->in);
			curr->type = PATH;
		}
		else if (str[i] == '>')
		{
			metachar = str[i];
			curr = add_token_back(curr, &curr->redir);
			curr->type = PATH;
		}
		else if (xrealloc(&curr->value.str, curr->value.len + 2, PARS_ALLOC))
			return (MEMORY_ERROR);
		else
		{
			curr->value.str[curr->value.len] = str[i];
			curr->value.len++;
			metachar |= 128;
		}
	}
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
		if (str[i] == '|')
			curr = add_token_back(curr, &curr->out);
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
		err = split_by_chev(ctx, curr, curr->value.str);


	return (err);
}
