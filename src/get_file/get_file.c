/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 04:29:57 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 19:37:21 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#define BUFFER_SIZE		4096

static int	file_record(const int fd, t_lst **lst, int *byte)
{
	t_lst	**elm;
	char	*buf;
	int		err;

	elm = lst;
	while (1)
	{
		if (xmalloc(&buf, BUFFER_SIZE + 1, TMP_ALLOC))
			return (MEMORY_ERROR);
		err = read(fd, buf, BUFFER_SIZE);
		if (err < 0)
			return (READ_ERROR);
		else if (!err)
			break ;
		if (xmalloc(elm, sizeof(t_lst), TMP_ALLOC))
			return (MEMORY_ERROR);
		buf[err] = '\0';
		*byte += err;
		(*elm)->data.len = err;
		(*elm)->data.str = buf;
		elm = &(*elm)->next;
	}
	if (!*lst)
		return (EMPTY_FILE_ERROR);
	return (NO_ERROR);
}



static int	merge_lst(t_lst *lst, char **str, const int byte)
{
	int		x;

	if (xmalloc(str, byte + 1, HISTORY_ALLOC))
		return (MEMORY_ERROR);
	(*str)[byte] = '\0';
	x = 0;
	while (lst)
	{
		while (*(lst->data.str))
			(*str)[x++] = *(lst->data.str)++;
		lst = lst->next;
	}
	return (NO_ERROR);
}

int	get_file(const int fd, char **str)
{
	t_lst	*lst;
	int		err;
	int		byte;

	lst = NULL;
	byte = 0;
	err = file_record(fd, &lst, &byte);
	if (err)
		return (err);
	if (merge_lst(lst, str, byte))
		return (MEMORY_ERROR);
	return (NO_ERROR);
}
