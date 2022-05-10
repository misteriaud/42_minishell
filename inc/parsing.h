/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:04:05 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/10 11:10:52 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <struct.h>
# include <memory.h>
# include <env.h>
# include <utils.h>
# include <unistd.h>

	// END = -1,
	// MAIN = 0, //				00000000
	// IN_WORD = 1, //				00000001
	// IN_SQ = 2, //				00000010	inside ''
	// IN_DQ = 4, // 				00000100	inside ""
	// A_PIP = 8, //				00001000	after |
	// A_L_CHEV = 16,//			00010000	after <
	// A_2L_CHEV = 48,//			00110000	after <<
	// A_R_CHEV = 64,//			01000000	after >
	// A_2R_CHEV = 192,//			11000000	after >>
	// AFTER_TOKEN = 256, //		100000000
	// ERROR = 255 //				11111111
typedef enum e_lexer_state {
	END = -1,
	MAIN = 0,
	IN_WORD = 1,
	IN_SQ = 2,
	IN_DQ = 4,
	A_PIP = 8,
	A_L_CHEV = 16,
	A_2L_CHEV = 48,
	A_R_CHEV = 64,
	A_2R_CHEV = 192,
	AFTER_TOKEN = 256,
	ERROR = 255
}	t_lexer_state;

typedef enum e_char_cat
{
	EOF = -1,
	WHITESPACE = 0,
	GENERAL = 1,
	SINGLE = 2,
	DOUBLE = 4,
	PIPE = 8,
	L_CHEVRON = 16,
	DL_CHEVRON = 48,
	R_CHEVRON = 64,
	DR_CHEVRON = 192
}	t_char_cat;

typedef struct s_state
{
	t_lexer_state	prev;
	t_lexer_state	curr;
}	t_state;

// local functions
t_char_cat		get_cat(char **str);
t_lexer_state	get_state(t_lexer_state state, t_char_cat cat);
t_err			new_branch(t_token **curr_token, t_state state,
					t_token_type type);
t_err			concat_token(t_ctx *ctx, t_token *token,
					t_state *state, t_str tmp);
void			move_forward(t_state *state, char **str);
t_token			*add_token_back(t_token *parent, t_token **first);

// public functions
t_err			parse(t_ctx *ctx, char *str);

#endif
