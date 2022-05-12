/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:55:21 by artblin           #+#    #+#             */
/*   Updated: 2022/05/12 16:01:42 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wildcard.h>

void	expand_wildcard(const char *directory)
{
	t_dir		*dir;
	t_entity	*entity;

	dir = opendir(directory);
	if (!dir)
	{
		perror(directory);
		return ;
	}

	while ((entity = readdir(dir)) != NULL)
	{
		printf("%s\n", entity->d_name);
	}
	closedir(dir);
}
