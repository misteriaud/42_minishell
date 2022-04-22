/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:29:44 by mriaud            #+#    #+#             */
/*   Updated: 2022/04/22 18:52:16 by mriaud           ###   ########.fr       */
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
	if (new_str(&tmp, doc->len + line->len + !!doc->len, PARS_ALLOC))
		return (PARSING_ERROR);
	while (++i < doc->len)
		tmp.str[i] = doc->str[i];
	if (doc->len)
		tmp.str[i] = '\n';
	while (++j < line->len)
		tmp.str[i + !!doc->len + j] = line->str[j];
	*doc = tmp;
	return (NO_ERROR);
}

t_err	prompt_heredoc(t_ctx *ctx)
{
	t_token	*curr;
	t_token	*curr_in;
	t_str	line;
	t_str	doc;

	curr = ctx->parse_tree;
	while (curr)
	{
		curr_in = curr->in;
		while (curr_in)
		{
			if (curr_in->type == HEREDOC)
			{
				line.str = NULL;
				line.len = 0;
				doc = line;
				while (1)
				{
					line.str = readline("> ");
					line.len = get_len(line.str);
					if (!compare(line.str, curr_in->value.str))
					{
						free(line.str);
						break ;
					}
					if (drop_variables(ctx, &line) || doccat(&doc, &line))
						return (PARSING_ERROR);
					free(line.str);
				}
				doccat(&doc, &(t_str){NULL, 0});
				curr_in->value = doc;
			}
			curr_in = curr_in->next;
		}
		curr = curr->out;
	}
	return (NO_ERROR);
}
