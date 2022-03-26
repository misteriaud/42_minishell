/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 22:51:50 by artblin           #+#    #+#             */
/*   Updated: 2021/12/18 07:00:44 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <stdlib.h>
# include <unistd.h>

typedef enum t_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum t_error
{
	NOERR,
	ERROR
}	t_error;

typedef struct t_lst
{
	int				file;
	char			*buffer;
	char			*line;
	char			*stash;
	struct t_lst	*next;
	size_t			s;
	size_t			x;
	ssize_t			b;
}	t_lst;

// return next line
char	*get_next_line(int fd);
// search end of line
t_bool	ft_search(const char *s, size_t *x);
// extract line from stash
t_error	ft_subtract(t_lst *e);
// rehash stash
t_error	ft_rehash(t_lst *e);
// generate line with buffer & stash
t_error	ft_generate(t_lst *e);
// merge stash & buffer remainder characters
t_error	ft_stock(t_lst *e);

#endif
