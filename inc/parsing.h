/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:04:05 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/25 21:04:09 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum state {
	GENERAL,
	IN_WORD,
	IN_VAR,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE,
	AFTER_PIPE,
	AFTER_L_CHEVRON,
	AFTER_2L_CHEVRON,
	AFTER_R_CHEVRON,
	AFTER_2R_CHEVRON,
};

enum character_category
{
    CHAR_GENERAL,
    CHAR_WHITESPACE = ' ',
    CHAR_AMPERSAND = '&',
    CHAR_PIPE = '|',
};

enum token_type
{
	cmd,
	path,
	arg,
	heredoc,
	var,
	text
};

typedef struct s_token
{
	enum token_type	type;
	struct s_token	*child;
	char			*value;
	struct s_token	*stdin;
	struct s_token	*arg;
	struct s_token	*stdout;
}	t_token;

int parse(t_token **first, char *str);
