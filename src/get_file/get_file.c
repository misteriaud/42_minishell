/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 04:29:57 by artblin           #+#    #+#             */
/*   Updated: 2022/03/26 21:45:30 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
static int	file_record(const int fd, t_file **lst, size_t *byte)
{
	t_file	**elm;
	char	*buf;
	int		err;

	*byte = 0;
	elm = lst;
	while (LOOP)
	{
		if (!mempush(&buf, sizeof(char), BUFFER_SIZE + 1))
			return (MEMORY_ERROR);
		err = read(fd, buf, BUFFER_SIZE);
		if (err < 0)
			return (READ_ERROR);
		else if (!err)
			break ;
		if (!mempush(elm, sizeof(t_file), 1))
			return (MEMORY_ERROR);
		*byte += err;
		buf[err] = '\0';
		(*elm)->buf = buf;
		elm = &(*elm)->nxt;
	}
	(*elm) = NULL;
	return (NO_ERROR);
}

static int	merge_file(t_file *lst, char **rec, const size_t byte)
{
	char	*str;

	if (!mempush(rec, sizeof(char), byte + 1))
		return (MEMORY_ERROR);
	(*rec)[byte] = '\0';
	str = *rec;
	while (lst)
	{
		while (*(lst->buf))
			*(str)++ = *(lst->buf)++;
		lst = lst->nxt;
	}
	return (NO_ERROR);
}*/

int	get_file(const int fd, char **str)
{
	(void)fd;
	(void)str;
	/*
	int			err;
	size_t		byte;
	t_file		*lst;

	err = file_record(*fd, &lst, &byte);
	if (err)
		return (err);
	if (merge_file(lst, str, byte))
		return (MEMORY_ERROR);
		*/
	return (NO_ERROR);
}
