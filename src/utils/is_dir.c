/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:24:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/11 09:17:26 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

t_err	is_dir(const char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (DIR_ERROR);
	return (NO_ERROR);
}
