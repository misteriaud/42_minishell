/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:56:33 by artblin           #+#    #+#             */
/*   Updated: 2022/05/12 11:31:18 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <termios.h>

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
	LEXING_ERROR = 0x70,
	PARSING_ERROR = 0x71,
	EMPTY_STR_ERROR = 0x80,
	NULL_PTR_ERROR = 0x81,
	NO_TOKEN_ERROR = 0x82,
	NO_BYTE_ERROR = 0x83,
	NO_VAR_ERROR = 0x84,
	NOT_EQUAL_ERROR = 0x85,
	EMPTY_FILE_ERROR = 0x86,
	UNKNOWN_EXEC_ERROR = 127,
	UNKNOWN_PATH_ERROR = 0x88,
	CTRL_C_ERROR = 130,
	TERM_ERROR = 0x90,
	PROCESS_ERROR = 0xA0,
	FORK_ERROR = 0xA1,
	BIN_UNKNOWN = 0xA2,
	PIPE_ERROR = 0xA3,
	REDIRECT_ERROR = 0xA4,
	WRITE_ERROR = 0xA5,
	SIGNAL_ERROR = 0xA6,
	EXIT_ERROR = 0xB0,
	VAR_ERROR = 0xC0,
	EXPORT_ERROR = 0xC2,
	UNSET_ERROR = 0xC3,
	DIR_ERROR = 126,
	REG_ERROR = 0xc4,
	PERMISSION_ERROR = 0xc5
}	t_err;

typedef struct s_built		t_built;
typedef struct s_ctx		t_ctx;
typedef struct s_token		t_token;
typedef struct termios		t_termios;
typedef						t_err (t_func)(t_ctx *, t_token *);

enum e_alloc_group
{
	PARS_ALLOC = 1,
	HISTORY_ALLOC,
	PATHS_ALLOC,
	ENV_ALLOC,
	EXEC_ALLOC,
	TMP_ALLOC,
	PROMPT_ALLOC
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
	PATH = 4,
	APPEND_PATH = 8,
	ARG = 16,
	HEREDOC = 32,
	AND_CMD = 64,
	// OR_CMD = 128,
	// EMPTY_CMD = 256
}	t_token_type;

struct s_token
{
	t_token_type	type;
	t_str			value;
	t_token			*in;
	t_token			*arg;
	t_token			*out;
	t_token			*redir;
	t_token			*next;
	t_token			*prev;
};

struct s_built
{
	t_str	cmd;
	t_func	*func;
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
	t_err			old_status;
};

#endif
