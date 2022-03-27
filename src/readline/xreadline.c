#include <readline.h>

static int	ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void move_cursor(t_line *line, int direction)
{
	if (line->pos + direction > line->len || line->pos + direction < 0)
		return ;
	if (direction == -1)
		write(STDOUT_FILENO, "\x1b[1D", 4);
	else
		write(STDOUT_FILENO, "\x1b[1C", 4);
	line->pos += direction;
}

t_err	add_letter(t_line *line)
{
	t_letter	*curr;
	int			i;
	t_letter	*new;

	i = 0;
	curr = line->first;
	while (curr && curr->next && ++i < line->pos)
		curr = curr->next;
	if (xmalloc(&new, sizeof(*new), LETTER_GROUP))
		return (MEMORY_ERROR);
	new->c = line->c;
	if (curr && line->pos)
	{
		new->next = curr->next;
		curr->next = new;
	}
	else
	{
		new->next = curr;
		line->first = new;
	}
	line->letter_added = 1;
	line->len++;
	return (NO_ERROR);
}

void remove_letter(t_line *line)
{
	t_letter *curr;
	t_letter *to_remove;
	int	 i;
	int pos;

	i = 0;
	pos = line->pos;
	if (line->c == 127)
		pos--;
	if (pos < 0 || pos >= line->len || !line->first)
		return ;
	if (!pos)
	{
		to_remove = line->first;
		line->first = to_remove->next;
		xfree(to_remove, LETTER_GROUP);
	}
	else
	{
		curr = line->first;
		while (curr && ++i < pos)
			curr = curr->next;
		to_remove = curr->next;
		curr->next = to_remove->next;
		xfree(to_remove, LETTER_GROUP);
	}
	if (line->c == 127)
		move_cursor(line, -1);
	line->len--;
}

void print_prefix(t_line *line)
{
	int to_right;

	to_right = ft_strlen(line->prefix);
	write(STDOUT_FILENO, line->prefix, to_right);
	to_right += 3;
	write(STDOUT_FILENO, " > ", 3);
}

t_err	display_line(t_line *line)
{
	t_letter *curr;
	int	 i;
	int	j;
	char *str;

	i = -1;
	if (line->cursor_move || !line->first)
		return (NO_ERROR);
	write(STDOUT_FILENO, "\x1b[s", 3);
	write(STDOUT_FILENO, "\x1b[0K", 4); //clean until end of line
	i = -1;
	j = -1;
	curr = line->first;
	if (xmalloc(&str, line->len + 1 - line->pos, 1))
		return (MEMORY_ERROR);
	while (curr && ++i < line->pos)
		curr = curr->next;
	while (curr)
	{
		str[++j] = curr->c;
		curr = curr->next;
	}
	write(STDOUT_FILENO, str, line->len + 1 - line->pos);
	write(STDOUT_FILENO, "\x1b[u", 3);
	if (line->letter_added)
	{
		move_cursor(line, 1);
		line->letter_added = 0;
	}
	xfree(str, 1);
	return (NO_ERROR);
}

t_err	line_to_ctx(t_ctx *ctx, t_line *line)
{
	t_letter *curr;

	ctx->curr_cmd.len = -1;
	curr = line->first;
	if (ctx->curr_cmd.str)
	{
		xfree(ctx->curr_cmd.str, READL_ALLOC);
		ctx->curr_cmd.str = NULL;
	}
	if (xmalloc(&ctx->curr_cmd.str, line->len + 1, READL_ALLOC))
		return (MEMORY_ERROR);
	while (curr)
	{
		ctx->curr_cmd.str[++(ctx->curr_cmd.len)] = curr->c;
		curr = curr->next;
	}
	return (NO_ERROR);
}

t_err special_key_handler(t_line *line)
{
	if (line->c == 3 || line->c == 4)
		return (READLINE_ERROR + line->c);
	if (line->c == '\x1b') {
		char seq[2];
		if (read(STDIN_FILENO, &seq[0], 1) != 1)
			return (NO_ERROR);
		if (read(STDIN_FILENO, &seq[1], 1) != 1)
			return (NO_ERROR);
		if (seq[0] == '[' && seq[1] == 'A')
			set_autocomp(line, UP);
		if (seq[0] == '[' && seq[1] == 'B')
			set_autocomp(line, DOWN);
		if (seq[0] == '[' && seq[1] == 'C')
		{
			move_cursor(line, 1);
			line->cursor_move = 1;
		}
		if (seq[0] == '[' && seq[1] == 'D')
		{
			move_cursor(line, -1);
			line->cursor_move = 1;
		}
	}
	return (NO_ERROR);
}
t_err key_handler(t_line *line)
{
	if (line->c == 127)
		remove_letter(line);
	else if (line->c == 126)
		remove_letter(line);
	else if (add_letter(line))
		return (MEMORY_ERROR);
	return (NO_ERROR);
}

t_err	xreadline(t_ctx *ctx, char *prefix)
{
	t_line	line;
	t_err	error;

	error = NO_ERROR;
	line.first = NULL;
	line.prefix = prefix;
	line.pos = 0;
	line.len = 0;
	line.cursor_move = 0;
	line.letter_added = 0;
	line.curr_hst = NULL;
	line.head_hst = ctx->history;
	if (get_cols(&line.cols))
		return (READLINE_ERROR);
	set_raw_term(ctx);
	print_prefix(&line);
	while (read(STDIN_FILENO, &line.c, 1) == 1 && line.c != 13) {
		if (line.c < 32)
			error = special_key_handler(&line);
		else
			error = key_handler(&line);
		if (error)
			break ;
		set_autocomp(&line, LAST);
		if (display_line(&line))
			return (READLINE_ERROR);
		display_autocomp(&line);
	}
	if (!error)
		error = line_to_ctx(ctx, &line);
	set_origin_term(ctx);
	write(STDOUT_FILENO, "\n", 1);
	return (error);
}
