#ifndef READLINE_H
# define READLINE_H

#include <unistd.h>
#include <termios.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

#include <memory.h>
#include <utils.h>
#include <struct.h>
#include <term.h>

typedef struct termios t_termios;
#define CTRL_KEY(q) ((q) & 0x1f)
#define MAIN_CTX 0
#define LETTER_GROUP 1
#define PARSING_GROUP 2
#define BUFFER_SIZE 4096

enum e_move {
	UP = 1,
	DOWN = -1,
	LAST = 0
};

typedef struct s_letter {
	unsigned char c;
	struct s_letter *next;
}				t_letter;

typedef struct s_line {
	unsigned char	c;
	t_letter		*first;
	char			*prefix;
	int				pos;
	int				offset;
	int				len;
	int				cursor_move;
	int				letter_added;
	t_lst			*head_hst;
	t_lst			*curr_hst;
}				t_line;

// local functions
int		history_match(t_line *line, t_lst *history_line);
void	set_autocomp(t_line *line, int prevnext);
void	display_autocomp(t_line *line);

// public functions
t_err	xreadline(t_ctx *ctx, char *prefix);

#endif
