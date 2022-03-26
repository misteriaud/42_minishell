/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:04:05 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/26 21:40:06 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <struct.h>

# define PARSING_ALLOC 1

# define ERR_ALLOC_FAILED 20
# define ERR_ADD_TOKEN 21

enum lexer_state {
	END = -1,
	MAIN = 0, //				00000000
	IN_WORD = 1, //				00000001
	IN_SINGLE_QUOTE = 2, //		00000010
	IN_DOUBLE_QUOTE = 4, // 	00000100
	AFTER_PIPE = 8, //			00001000
	AFTER_L_CHEVRON = 16,//		00010000
	AFTER_2L_CHEVRON = 48,//	00110000
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
	NULL = 0,
	CMD = 2,
	CMD_VAR = 3,
	PATH = 4,
	PATH_VAR = 5,
	APPEND_PATH = 8,
	APPEND_PATH_VAR = 9,
	ARG = 16,
	ARG_VAR = 17,
	HEREDOC = 32,
	HEREDOC_VAR = 33,
};

typedef struct s_token
{
	enum token_type	type;
	t_str			value;
	struct s_token	*stdin;
	struct s_token	*arg;
	struct s_token	*stdout;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

int parse(t_token **first, char *str);

#endif
