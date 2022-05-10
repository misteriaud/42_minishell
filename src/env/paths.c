/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:13:26 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 17:54:25 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	get_exec_path(t_ctx *ctx, t_str *exec)
{
	t_lst	*elm;
	t_str	exec_path;

	if (is_containing_set(exec->str, "/"))
	{
		expand_path(ctx, exec);
		if (is_dir(exec->str))
			return (DIR_ERROR);
		if (!access(exec->str, X_OK))
			return (NO_ERROR);
		return (UNKNOWN_EXEC_ERROR);
	}
	elm = ctx->paths;
	while (elm)
	{
		if (new_str(&exec_path, elm->data.len + exec->len + 1, PARS_ALLOC))
			return (MEMORY_ERROR);
		merge(&exec_path, &elm->data, exec, '/');
		if (!access(exec_path.str, X_OK))
		{
			xfree(exec->str, PARS_ALLOC);
			return (*exec = exec_path, NO_ERROR);
		}
		xfree(exec_path.str, PARS_ALLOC);
		elm = elm->next;
	}
	return (UNKNOWN_EXEC_ERROR);
}

t_err	refresh_paths(t_ctx *ctx)
{
	t_str	paths;

	xfree_group(PATHS_ALLOC);
	ctx->paths = NULL;
	if (get_variable(ctx, "PATH", &paths))
		return (NO_VAR_ERROR);
	if (split_lst_normal(&ctx->paths, paths.str, ':', PATHS_ALLOC))
		return (MEMORY_ERROR);
	return (NO_ERROR);
}

t_err	get_exec_arg(char ***arg, t_token *parse)
{
	t_token		*elm;
	int			size;
	int			x;

	size = 0;
	elm = parse->arg;
	while (elm && ++size)
		elm = elm->next;
	if (xmalloc(arg, (size + 2) * sizeof(char *), TMP_ALLOC))
		return (MEMORY_ERROR);
	elm = parse->arg;
	x = 0;
	(*arg)[x++] = parse->value.str;
	while (elm)
	{
		(*arg)[x++] = elm->value.str;
		elm = elm->next;
	}
	return (NO_ERROR);
}

t_err	expand_path(t_ctx *ctx, t_str *path)
{
	t_str	new;
	t_str	home;
	t_str	cut;

	if (!path || !path->str)
		return (NULL_PTR_ERROR);
	if (*(path->str) == '~')
	{
		cut.len = path->len - 1;
		cut.str = path->str + 1;
		if (!get_variable(ctx, "HOME", &home))
		{
			new_str(&new, home.len + cut.len, PARS_ALLOC);
			merge(&new, &home, &cut, 0);
			xfree(path->str, PARS_ALLOC);
			path->str = new.str;
			path->len = new.len;
		}
	}
	return (NO_ERROR);
}
