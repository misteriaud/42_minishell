/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:56:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 17:23:53 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

# include <termios.h>

typedef enum e_err
{
	NO_ERROR = 0,
	MEMORY_ERROR = 0x10,
	OPEN_ERROR = 0x20,
	READ_ERROR = 0x30,
	OVERFLOW_ERROR = 0x40,
	ARG_ERROR = 0x50,
	OPTION_ERROR = 0x60,
	LEXING_ERROR = 0x70,
	PARSING_ERROR = 0x71,
	EMPTY_STR_ERROR = 0x80,
	NULL_PTR_ERROR = 0x81,
	NO_TOKEN_ERROR = 0x82,
	NO_BYTE_ERROR = 0x83
}	t_err;

enum e_alloc_group
{
	PARS_ALLOC,
	HISTORY_ALLOC,
	ENV_ALLOC,
	TMP_ALLOC,
};

typedef struct s_str
{
	char			*str;
	int				len;
}	t_str;

typedef struct s_lst
{
	t_str			data;
	struct s_lst	*next;
	struct s_hst	*prev;
}	t_lst;

typedef struct s_hst
{
	t_str			cmd;
	struct s_hst	*next;
	struct s_hst	*prev;
}	t_hst;

typedef struct s_env
{
	t_str			key;
	t_str			value;
	struct s_env	*next;
}	t_env;


//PARSING STRUCT
typedef enum e_token_type
{
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
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	t_str			value;
	struct s_token	*in;
	struct s_token	*arg;
	struct s_token	*out;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;


// CONTEXT STRUCT
typedef struct s_ctx
{
	int				fd_history;
	t_hst			*history;
	t_env			*env;
	t_env			*var;
	struct termios	raw_term;
	struct termios	origin_term;
	t_str			curr_cmd;
	t_token			*parse_tree;

}	t_ctx;

#endif
