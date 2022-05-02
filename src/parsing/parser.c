/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/02 11:25:14 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>
#include <stdio.h>

static	t_err	log_error(t_err error, char *str)
{
	if (!error)
		return (error);
	if (!*str)
		printf("minishell: erreur lors de la lecture de la chaîne de caractères\n");
	else
		printf("minishell: syntax error near unexpected token ' %c '\n", *str);
	return (error);
}

static	t_err	ft_state_lane(t_state *state, char **str, int *i)
{
	while ((state->curr > 0 && state->curr & IN_WORD)
		|| (state->curr == state->prev && state->curr < 8 && state->curr))
	{
		(*i)++;
		move_forward(state, str);
	}
	if (state->curr == ERROR)
		return (LEXING_ERROR);
	return (NO_ERROR);
}

static t_err	feed_token(t_ctx *ctx, t_token *token,
	t_state *state, char **str)
{
	t_str	tmp;
	int		i;
	char	*end;

	tmp = (t_str){NULL, 0};
	i = 0;
	if ((state->curr > 0 && state->curr & IN_WORD)
		|| (state->curr == state->prev && state->curr < 8 && state->curr))
	{
		end = *str;
		if (ft_state_lane(state, &end, &tmp.len))
			return (LEXING_ERROR);
		if (xmalloc(&tmp.str, tmp.len + 1, PARS_ALLOC))
			return (MEMORY_ERROR);
		while (i++ < tmp.len)
			tmp.str[i - 1] = *((*str)++);
		*str = end;
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
		return (log_error(LEXING_ERROR, str));
	if (!*str)
		return (log_error(NO_ERROR, str));
	else if ((state.prev & A_PIP)
		&& new_branch(&token, state, CMD))
		return (log_error(MEMORY_ERROR, str));
	else if (state.prev & (A_L_CHEV | A_R_CHEV | A_2L_CHEV | A_2R_CHEV) && state.curr < 8
		&& new_branch(&token, state, PATH))
		return (log_error(MEMORY_ERROR, str));
	else if (state.prev == AFTER_TOKEN && state.curr < 8
		&& new_branch(&token, state, ARG))
		return (log_error(MEMORY_ERROR, str));
	if (feed_token(ctx, token, &state, &str))
		return (log_error(MEMORY_ERROR, str));
	return (generate_token(ctx, token, state, str));
}

t_err	parse(t_ctx *ctx, char *str)
{
	t_state	state;

	if (xmalloc(&ctx->parse_tree, sizeof(*ctx->parse_tree), PARS_ALLOC))
		return (MEMORY_ERROR);
	ctx->parse_tree->type = CMD;
	state.prev = MAIN;
	state.curr = get_state(MAIN, get_cat(&str));
	return (generate_token(ctx, ctx->parse_tree, state, str));
}
