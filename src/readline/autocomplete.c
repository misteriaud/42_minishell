/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 18:43:16 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/27 18:37:03 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline.h>

int history_match(t_line *line, t_lst *history_line)
{
	int	i;
	t_letter *curr;

	i = 0;
	curr = line->first;
	if (!curr)
		return (1);
	while(curr && history_line && history_line->data.str[i])
	{
		if (curr->c != history_line->data.str[i])
			return (0);
		curr = curr->next;
		i++;
	}
	if (!curr)
		return (1);
	return (0);
}

void set_autocomp(t_line *line, int prevnext)
{
	if (!line->head_hst
		|| (line->curr_hst && history_match(line, line->curr_hst) && !prevnext))
		return ;
	if (!prevnext || line->curr_hst)
		line->curr_hst = line->head_hst;
	if (prevnext == UP && line->curr_hst->next)
		line->curr_hst = line->curr_hst->next;
	if (prevnext == DOWN && line->curr_hst->prev)
		line->curr_hst = line->curr_hst->prev;
	while (line->curr_hst)
	{
		if (history_match(line, line->curr_hst))
			return ;
		line->curr_hst = line->curr_hst->prev;
	}
}

void display_autocomp(t_line *line)
{
	int	i;
	int j;
	t_letter *curr;

	if(line->cursor_move || !line->curr_hst)
	{
		line->cursor_move = 0;
		return ;
	}
	i = 0;
	j = -1;
	curr = line->first;
	while(curr)
	{
		curr = curr->next;
		i++;
	}
	write(STDOUT_FILENO, "\x1b[s", 3);
	while (line->pos + ++j < line->len)
		write(STDOUT_FILENO, "\x1b[1C", 4);
	write(STDOUT_FILENO, "\033[0;90m", 7);
	while (line->curr_hst->data.str[i])
		write(STDOUT_FILENO, &line->curr_hst->data.str[i++], 1);
	write(STDOUT_FILENO, "\033[0m", 4);
	write(STDOUT_FILENO, "\x1b[u", 3);
}
