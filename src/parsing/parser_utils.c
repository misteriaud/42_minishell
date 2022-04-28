/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:15:44 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/28 14:34:37 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

t_err	add_token_back(t_token **parent, t_token **first)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*dest;

	prev = NULL;
	curr = *first;
	if (xmalloc(&dest, sizeof(*dest), PARS_ALLOC))
		return (MEMORY_ERROR);
	dest->prev = *parent;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*first = dest;
	else
		prev->next = dest;
	*parent = dest;
	return (NO_ERROR);
}

t_err	new_branch(t_token **curr_token, char type)
{
	while ((*curr_token)->type != CMD)
		*curr_token = (*curr_token)->prev;
	if (type == '|' && !add_token_back(curr_token, &(*curr_token)->out))
		(*curr_token)->type = 0;
	else if (type == '<' && !add_token_back(curr_token, &(*curr_token)->in))
		(*curr_token)->type = type;
	else if (type == '>' && !add_token_back(curr_token, &(*curr_token)->redir))
		(*curr_token)->type = type;
	else if (!add_token_back(curr_token, &(*curr_token)->arg))
		(*curr_token)->type = 1;
	else
		return (MEMORY_ERROR);
	return (NO_ERROR);
}

void	move_forward(t_state *state, char **str)
{
	*str = *str + 1;
	state->prev = state->curr;
	state->curr = get_state(state->prev, get_cat(**str));
}

t_err	concat_token(t_ctx *ctx, t_token *token, t_state *state, t_str tmp)
{
	t_str	dest;

	dest = (t_str){NULL, 0};
	if (!(state->prev & IN_SQ) && drop_variables(ctx, &tmp))
		return (MEMORY_ERROR);
	if (!token->value.str)
		token->value = tmp;
	else if (new_str(&dest, tmp.len + token->value.len, PARS_ALLOC)
		|| merge(&dest, &token->value, &tmp, 0))
		return (MEMORY_ERROR);
	if (dest.len)
	{
		xfree(token->value.str, PARS_ALLOC);
		token->value = dest;
	}
	return (NO_ERROR);
}
