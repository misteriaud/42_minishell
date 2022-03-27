/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:04:05 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/27 12:26:47 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include <struct.h>

# define PARS_GROUP 1

enum lexer_state {
	END = -1,
	MAIN = 0, //				00000000
	IN_WORD = 1, //				00000001
	IN_SQ = 2, //				00000010	inside ''
	IN_DQ = 4, // 				00000100	inside ""
	A_PIP = 8, //				00001000	after |
	A_L_CHEV = 16,//			00010000	after <
	A_2L_CHEV = 48,//			00110000	after <<
	A_R_CHEV = 64,//			01000000	after >
	A_2R_CHEV = 192,//			11000000	after >>
	CHEV_WAIT = 512, //			1000000000	wait for next chevron
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

// local functions
t_err	get_cat(char c);
t_err	get_state(int state, enum char_cat cat);

// public functions
t_err	parse(t_token **first, char *str);

#endif
