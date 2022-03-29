/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 16:43:29 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_token	*add_token_back(t_token *parent, t_token **first)
{
	t_token	*curr;
	t_token	*prev;
	t_token	*dest;

	prev = NULL;
	curr = *first;
	if (xmalloc(&dest, sizeof(*dest), PARS_ALLOC))
		return (NULL);
	dest->prev = parent;
	while (curr && curr->next)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev)
		*first = dest;
	else
		curr->next = dest;
	return (dest);
}

static t_err	new_branch(t_token **curr_token, t_state state, t_token_type type)
{
	while (state.prev && (*curr_token)->type != CMD)
		*curr_token = (*curr_token)->prev;
	if (state.prev == MAIN || state.prev & (A_PIP | A_R_CHEV))
		*curr_token = add_token_back(*curr_token, &(*curr_token)->out);
	else if (state.prev & A_L_CHEV)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->in);
	else if (state.prev & AFTER_TOKEN && (*curr_token)->type == ARG)
		*curr_token = add_token_back(*curr_token, &(*curr_token)->next);
	else
		*curr_token = add_token_back(*curr_token, &(*curr_token)->arg);
	if (!curr_token)
		return (MEMORY_ERROR);
	(*curr_token)->type = type;
	if ((state.prev & 255) == A_2L_CHEV || (state.prev & 255) == A_2R_CHEV)
		(*curr_token)->type += 4 + ((state.prev & 255) == A_2L_CHEV) * 24;
	return (NO_ERROR);
}

static inline void	move_forward(t_state *state, char **str)
{
		*str = *str + 1;
		state->prev = state->curr;
		state->curr = get_state(state->prev, get_cat(**str));
}

static t_err	feed_token(t_ctx *ctx, t_token *token, t_state *state, char **str)
{
	t_str	tmp;
	t_str	dest;
	int		to_convert;

	tmp = (t_str){NULL, 0};
	dest = tmp;
	to_convert = 0;
	if (state->curr & IN_DQ || (state->curr & IN_WORD && **str == '$'))
		to_convert = 1;
	while ((state->curr > 0 && state->curr & (IN_WORD | VAR_CHAR)) || (state->curr == state->prev && state->curr < 8 && state->curr))
	{
		if (xrealloc(&tmp.str, (tmp.len++) + 1, PARS_ALLOC))
			return (MEMORY_ERROR);
		tmp.str[tmp.len - 1] = **str;
		move_forward(state, str);
	}
	if (tmp.len)
	{
		if (to_convert && replace_var(ctx, &tmp))
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
	}
	else
		move_forward(state, str);
	return (NO_ERROR);
}

static t_err	generate_token(t_ctx *ctx, t_token *token, t_state state, char *str)
{
	if (state.curr > 1 && state.curr % 2)
		return (LEXING_ERROR);
	if (!*str)
		return (NO_ERROR);
	else if ((state.prev & A_PIP) && (state.prev & 0x3FF) < 8
		&& new_branch(&token, state, CMD))
		return (MEMORY_ERROR);
	else if (state.prev & (A_L_CHEV | A_R_CHEV) && (state.curr & 0x3FF) < 8
		&& new_branch(&token, state, PATH))
		return (MEMORY_ERROR);
	else if (state.prev == AFTER_TOKEN && (state.curr & 0x3FF) < 8
		&& new_branch(&token, state, ARG))
		return (MEMORY_ERROR);
	if (feed_token(ctx, token, &state, &str))
		return (MEMORY_ERROR);
	printf("\'%c\'(prev_state: %d, state:%d) %s(type %d)\n", *str, state.prev, state.curr, token->value.str, token->type);
	return (generate_token(ctx, token, state, str));
}

t_err	parse(t_ctx *ctx, char *str)
{
	t_state	state;

	if (xmalloc(&ctx->parse_tree, sizeof(*ctx->parse_tree), PARS_ALLOC))
		return (MEMORY_ERROR);
	ctx->parse_tree->type = CMD;
	state.prev = MAIN;
	state.curr = get_state(MAIN, get_cat(*str));
	return (generate_token(ctx, ctx->parse_tree, state, str));
}
