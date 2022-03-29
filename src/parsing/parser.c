/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/29 22:17:09 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static t_err	feed_token(t_ctx *ctx, t_token *token,
	t_state *state, char **str)
{
	t_str	tmp;

	tmp = (t_str){NULL, 0};
	while ((state->curr > 0 && state->curr & IN_WORD)
		|| (state->curr == state->prev && state->curr < 8 && state->curr))
	{
		if (xrealloc(&tmp.str, (tmp.len++) + 1, PARS_ALLOC))
			return (MEMORY_ERROR);
		tmp.str[tmp.len - 1] = **str;
		move_forward(state, str);
	}
	if (tmp.len)
		return (concat_token(ctx, token, state, tmp));
	else
		move_forward(state, str);
	return (NO_ERROR);
}

// printf("\'%c\'(prev_state: %d, state:%d) %s(type %d)\n", *str,
	// state.prev, state.curr, token->value.str, token->type);
static t_err	generate_token(t_ctx *ctx, t_token *token,
	t_state state, char *str)
{
	if (state.curr > 1 && state.curr % 2)
		return (LEXING_ERROR);
	if (!*str)
		return (NO_ERROR);
	else if ((state.prev & A_PIP) && state.curr < 8
		&& new_branch(&token, state, CMD))
		return (MEMORY_ERROR);
	else if (state.prev & (A_L_CHEV | A_R_CHEV) && state.curr < 8
		&& new_branch(&token, state, PATH))
		return (MEMORY_ERROR);
	else if (state.prev == AFTER_TOKEN && state.curr < 8
		&& new_branch(&token, state, ARG))
		return (MEMORY_ERROR);
	if (feed_token(ctx, token, &state, &str))
		return (MEMORY_ERROR);
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
