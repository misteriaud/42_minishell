/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:56:33 by artblin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/30 01:35:15 by mriaud           ###   ########.fr       */
=======
/*   Updated: 2022/03/30 11:43:07 by artblin          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

# include <termios.h>

typedef struct s_built		t_built;
typedef struct s_ctx		t_ctx;
typedef struct s_token		t_token;
typedef struct termios		t_termios;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_err
{
	NO_ERROR = 0,
	NO_ENV_ERROR = 0x01,
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
	NO_BYTE_ERROR = 0x83,
	NO_VAR_ERROR = 0x84,
	NOT_EQUAL_ERROR = 0x85,
	EMPTY_FILE_ERROR = 0x86,
	UNKNOWN_EXEC_ERROR = 0x87,
	TERM_ERROR = 0x90,
	PROCESS_ERROR = 0xA0,
	FORK_ERROR = 0xA1,
	BIN_UNKNOWN = 0xA2,
	PIPE_ERROR = 0xA3
}	t_err;

enum e_alloc_group
{
	PARS_ALLOC = 1,
	HISTORY_ALLOC,
	PATHS_ALLOC,
	ENV_ALLOC,
	EXEC_ALLOC,
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
	struct s_lst	*prev;
}	t_lst;

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


struct s_token
{
	t_token_type	type;
	t_str			value;
	t_token			*in;
	t_token			*arg;
	t_token			*out;
	t_token			*next;
	t_token			*prev;
};

struct s_built
{
	t_str	cmd;
	t_err	(*func)(t_ctx *ctx, t_token *args);
};

// CONTEXT STRUCT
struct s_ctx
{
	int				fd_history;
	t_lst			*history;
	t_lst			*paths;
	t_env			*env;
	char			**exec_env;
	t_built			built[7];
	t_termios		raw_term;
	t_termios		origin_term;
	t_token			*parse_tree;
};





#endif
