/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:57:54 by mriaud            #+#    #+#             */
/*   Updated: 2022/03/27 12:43:26 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
static void		esc_mode(uint8_t *c)
{
	read(STDIN_FILENO, c, 1);
	if (*c == 91)
	{
		read(STDIN_FILENO, c, 1);
		// up arrow
		if (*c == 'A')
			write(1, "\x1B[A", 3);	// move cursor up
		// down arrow
		if (*c == 'B')
			write(1, "\x1B[B", 3);	// move cursor down
		// right arrow
		if (*c == 'C')
			write(1, "\x1B[C", 3);	// move cursor right
		// left arrow
		if (*c == 'D')
			write(1, "\x1B[D", 3);	// move cursor left
	}
	else
		write(1, c, 1);
}

t_err	prompt()
{
	char	*buf;
	char	*checkpoint;
	int		x;

	x = 0;
	buf = getcwd(NULL, 0);
	if (!buf)
		return (MEMORY_ERROR);
	checkpoint = buf;
	while (buf[x])
	{
		if (buf[x] == '/' && buf[x + 1])
			checkpoint = &(buf[x + 1]);
		x++;
	}
	printf("%s ", checkpoint);
	fflush(stdout);
	free(buf);
	return (NO_ERROR);
}

void	run(t_ctx *ctx)
{
	uint8_t		c = 0;

	prompt();
	set_raw_term(ctx);
	while (1 == read(0, &c, 1))
	{

		if (c == 27)
			esc_mode(&c);
		else if (c == 3)
		{
			break;
		}
		else
			write(1, &c, 1);
	}
	set_origin_term(ctx);
}*/

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;

	t_ctx	ctx;
	init_term(&ctx);

	// if(parse(&ctx.parse_tree, av[1]))
	// 	printf("ERROR\n");
	/*
	run(&ctx);
	write(1, "\nexiting...\n", 12);
	*/

	xfree_all();
	return (0);
}
