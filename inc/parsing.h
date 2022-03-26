/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:04:05 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/26 14:12:47 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define PARSING_ALLOC 1

# define ERR_ALLOC_FAILED 20

enum lexer_state {
	MAIN = 0, //				00000000
	IN_WORD = 1, //				00000001
	IN_SINGLE_QUOTE = 2, //		00000010
	IN_DOUBLE_QUOTE = 4, // 	00000100
	AFTER_PIPE = 8, //			00001000
	AFTER_L_CHEVRON = 16,//		00010000
	AFTER_2L_CHEVRON = 32,//	00110000
	AFTER_R_CHEVRON = 64,//		01000000
	AFTER_2R_CHEVRON = 192,//	11000000
	CHEVRON_WAITING = 512, //	1000000000
	AFTER_TOKEN = 256, //		100000000
	ERROR = 255 //				11111111
};

enum char_cat
{
	EOF = -1,
	WHITESPACE = 0,
	GENERAL = 1,
	SINGLE = 2,
	DOUBLE = 4,
	PIPE = 8,
	L_CHEVRON = 16,
	R_CHEVRON = 64,
};

enum token_type
{
	cmd,
	path,
	append_path,
	arg_w_var,
	arg_wo_var,
	heredoc,
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

#endif
