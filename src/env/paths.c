/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:13:26 by artblin           #+#    #+#             */
/*   Updated: 2022/03/28 16:13:01 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	get_exec_path(t_ctx *ctx, t_str *exec)
{
	t_lst	*elm;
	t_str	exec_path;

	elm = ctx->paths;
	while (elm)
	{
		merge(&exec_path, &elm->data, exec, '/');
		if (!access(exec_path.str, X_OK))
		{
			xfree(exec->str, PARS_ALLOC);
			//xfree_group(TMP_ALLOC);
			*exec = exec_path;
			return (NO_ERROR);
		}
		elm = elm->next;
	}
	xfree_group(TMP_ALLOC);
	return (UNKNOWN_EXEC_ERROR);
}

t_err	refresh_paths(t_ctx *ctx)
{
	t_str	paths;

	xfree_group(PATHS_ALLOC);
	if (get_env(ctx, "PATH", &paths))
		return (NO_VAR_ERROR);
	if (split_lst_normal(&ctx->paths, paths.str, ':', PATHS_ALLOC))
		return (MEMORY_ERROR);
	return (NO_ERROR);
}
