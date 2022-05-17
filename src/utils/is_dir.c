/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:24:08 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/17 12:45:07 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

t_err	is_dir(const char *path)
{
	struct stat	path_stat;

	path_stat.st_mode = (mode_t){0};
	stat(path, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
		return (DIR_ERROR);
	return (NO_ERROR);
}
