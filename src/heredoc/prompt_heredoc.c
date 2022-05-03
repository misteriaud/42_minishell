/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:29:44 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/03 14:12:38 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <heredoc.h>

t_err	doccat(t_str *doc, const t_str *line)
{
	t_str	tmp;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tmp = *doc;
	if (new_str(&tmp, doc->len + line->len + 1, PARS_ALLOC))
		return (PARSING_ERROR);
	while (++i < doc->len)
		tmp.str[i] = doc->str[i];
	while (++j < line->len)
		tmp.str[i + j] = line->str[j];
	tmp.str[i + j] = '\n';
	*doc = tmp;
	return (NO_ERROR);
}

static inline t_err	get_doc(t_ctx *ctx, t_str *dest)
{
	t_str	line;
	t_str	doc;

	line.str = NULL;
	line.len = 0;
	doc = line;
	while (1)
	{
		line.str = readline("> ");
		line.len = get_len(line.str);
		if (!line.str || !compare(line.str, dest->str))
		{
			if (line.str)
				free(line.str);
			else
				putstr_err("bash: here-doc recieve EOF\n");
			break ;
		}
		if (drop_variables(ctx, &line) || doccat(&doc, &line))
			return (PARSING_ERROR);
		free(line.str);
	}
	*dest = doc;
	return (NO_ERROR);
}

t_err	prompt_heredoc(t_ctx *ctx)
{
	t_token	*curr;
	t_token	*curr_in;

	curr = ctx->parse_tree;
	while (curr)
	{
		curr_in = curr->in;
		while (curr_in)
		{
			if (curr_in->type == HEREDOC && get_doc(ctx, &curr_in->value))
				return (PARSING_ERROR);
			curr_in = curr_in->next;
		}
		curr = curr->out;
	}
	return (NO_ERROR);
}
