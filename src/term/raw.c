/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:30:31 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 21:07:59 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>

void	init_term(t_ctx *ctx)
{
	tcgetattr(0, &ctx->origin_term);
	ctx->raw_term = ctx->origin_term;

	ctx->raw_term.c_iflag &= ~(		IXON		// disable Ctrl-S and Ctrl-Q
								|	ICRNL);		// disable Ctrl-M
	ctx->raw_term.c_lflag &= ~(		ECHO		// disable echo
								|	ICANON		// non-canonical mode
								|	ISIG		// disable Ctrl-C and Ctrl-Z
								|	IEXTEN);	// disable Ctrl-V and Ctrl-O
	ctx->raw_term.c_oflag &= ~(		OPOST);		// \n is move down, \r is carriage return
}

void	set_raw_term(t_ctx *ctx)
{
	tcsetattr(0, TCSAFLUSH, &ctx->raw_term);
}

void	set_origin_term(t_ctx *ctx)
{
	tcsetattr(0, TCSAFLUSH, &ctx->origin_term);
}

t_err	get_cols(int *cols)
{
	struct winsize ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
		return (TERM_ERROR);
	else
		*cols = ws.ws_col;
	return (NO_ERROR);
}
