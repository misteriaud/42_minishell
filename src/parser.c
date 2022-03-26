/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:06:19 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/26 23:32:08 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int get_cat(char c)
{
	if (!c)
		return EOF;
	if (c == ' ')
		return WHITESPACE;
	if (c == '|')
		return PIPE;
	if (c == '\'')
		return SINGLE;
	if (c == '"')
		return DOUBLE;
	if (c == '<')
		return L_CHEVRON;
	if (c == '>')
		return R_CHEVRON;
	return GENERAL;
}

int get_state(int state, enum char_cat cat)
{
	if (cat == EOF && state & 766)
		return (ERROR);
	if (cat == EOF)
		return (END);
	if (cat == WHITESPACE && state != IN_WORD)
	{
		if (state & CHEVRON_WAITING)
			return (state ^ CHEVRON_WAITING);
		return (state);
	}
	if ((state == MAIN && cat < 8) || state == AFTER_TOKEN)
	{
		if (cat & (L_CHEVRON | R_CHEVRON))
			return (cat + CHEVRON_WAITING);
		return (cat);
	}
	if (state & (AFTER_PIPE | AFTER_L_CHEVRON | AFTER_2L_CHEVRON | AFTER_R_CHEVRON | AFTER_2R_CHEVRON) && cat < 8)
			return (cat);
	if (state & IN_WORD)
	{
		if (!cat) // si whitespace
			return (AFTER_TOKEN); // on retourne dans le main
		if (cat & (L_CHEVRON | R_CHEVRON))
			return (cat + CHEVRON_WAITING);
		return (cat);
	}
	if (state & (IN_SINGLE_QUOTE | IN_DOUBLE_QUOTE)) //in quotes
	{
		if (cat & state) //si fermeture de quote
			return (AFTER_TOKEN);
		return (state);
	}
	if (state & CHEVRON_WAITING && cat & (L_CHEVRON | R_CHEVRON))
		return ((state << 1) + cat);
	return (ERROR);
}

t_token *add_token_back(t_token *parent, t_token **first)
{
	t_token *curr;
	t_token *prev;
	t_token	*dest;

	prev = NULL;
	curr = *first;
	if (xmalloc(&dest, sizeof(*dest), PARSING_ALLOC))
		return (0);
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

int	generate_token(t_token *curr_token, int prev_state, char *str)
{
	int	state;
	int	cat;

	cat = get_cat(*str);
	state = get_state(prev_state, cat);
	if (state > 1 && state % 2)
		return (1);
	if (!*str)
		return (0);
	else if ((prev_state == MAIN) && state < 8) //add CMD
	{
		if (!curr_token->type)
			curr_token->type = CMD;
		if (state == IN_DOUBLE_QUOTE)
			curr_token->type += 1;
		if (state == 1)
		{
			if (xrealloc(&curr_token->value.str, (curr_token->value.len++) + 1, PARSING_ALLOC))
				return (ERR_ALLOC_FAILED);
			curr_token->value.str[curr_token->value.len - 1] = *str;
		}
	}
	else if (prev_state & (AFTER_PIPE) && state < 8)
	{
		while (curr_token->type != CMD)
			curr_token = curr_token->prev;
		curr_token = add_token_back(curr_token, &curr_token->stdout);
		if (!curr_token)
			return (ERR_ADD_TOKEN);
		curr_token->type = CMD;
		if (state == IN_DOUBLE_QUOTE)
			curr_token->type += 1;
		printf("%s->stdout (CMD)\n", curr_token->prev->value.str);
		if (state == 1)
		{
			if (xrealloc(&curr_token->value.str, (curr_token->value.len++) + 1, PARSING_ALLOC))
				return (ERR_ALLOC_FAILED);
			curr_token->value.str[curr_token->value.len - 1] = *str;
		}
	}
	else if (prev_state & (AFTER_R_CHEVRON) && state < 8)
	{
		while (curr_token->type != CMD)
			curr_token = curr_token->prev;
		curr_token = add_token_back(curr_token, &curr_token->stdout);
		if (!curr_token)
			return (ERR_ADD_TOKEN);
		curr_token->type = PATH;
		if ((prev_state & 255) == AFTER_2R_CHEVRON)
			curr_token->type = APPEND_PATH;
		if (state == IN_DOUBLE_QUOTE)
			curr_token->type += 1;
		printf("%s->stdout (PATH)\n", curr_token->prev->value.str);
		if (state == 1)
		{
			if (xrealloc(&curr_token->value.str, (curr_token->value.len++) + 1, PARSING_ALLOC))
				return (ERR_ALLOC_FAILED);
			curr_token->value.str[curr_token->value.len - 1] = *str;
		}
	}
	else if (prev_state & (AFTER_L_CHEVRON) && state < 8)
	{
		while (curr_token->type != CMD)
			curr_token = curr_token->prev;
		curr_token = add_token_back(curr_token, &curr_token->stdin);
		if (!curr_token)
			return (ERR_ADD_TOKEN);
		curr_token->type = PATH;
		if ((prev_state & 255) == AFTER_2L_CHEVRON)
			curr_token->type = HEREDOC;
		if (state == IN_DOUBLE_QUOTE)
			curr_token->type += 1;
		printf("%s->stdin (PATH)\n", curr_token->prev->value.str);
		if (state == 1)
		{
			if (xrealloc(&curr_token->value.str, (curr_token->value.len++) + 1, PARSING_ALLOC))
				return (ERR_ALLOC_FAILED);
			curr_token->value.str[curr_token->value.len - 1] = *str;
		}
	}
	else if (prev_state & AFTER_TOKEN && state < 8)
	{
		if (curr_token->type == ARG)
		{
			curr_token = add_token_back(curr_token, &curr_token->next);
			printf("%s->next (ARG)\n", curr_token->prev->value.str);
		}
		else
		{
			curr_token = add_token_back(curr_token, &curr_token->next);
			printf("%s->arg (ARG)\n", curr_token->prev->value.str);
		}
		if (!curr_token)
			return (ERR_ADD_TOKEN);
		curr_token->type = ARG;
		if (state == IN_DOUBLE_QUOTE)
			curr_token->type += 1;
		if (state == 1)
		{
			if (xrealloc(&curr_token->value.str, (curr_token->value.len++) + 1, PARSING_ALLOC))
				return (ERR_ALLOC_FAILED);
			curr_token->value.str[curr_token->value.len - 1] = *str;
		}
	}
	else if (prev_state & (IN_WORD | IN_SINGLE_QUOTE | IN_DOUBLE_QUOTE) && state < 8)
	{
		if (xrealloc(&curr_token->value.str, (curr_token->value.len++) + 1, PARSING_ALLOC))
			return (ERR_ALLOC_FAILED);
		curr_token->value.str[curr_token->value.len - 1] = *str;
	}
	printf("char \'%c\', state: %d, cat: %d, type: %d, value: \"%s\"\n", *str, state, cat, curr_token->type, curr_token->value.str);
	return (generate_token(curr_token, state, str + 1));
}

int parse(t_token **first, char *str)
{
	t_token				*dest;

	(void)first;
	if (xmalloc(&dest, sizeof(*dest), PARSING_ALLOC))
		return (ERR_ALLOC_FAILED);
	if (generate_token(dest, MAIN, str))
		printf("PAS BON\n");
	return (1);
}
