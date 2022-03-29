/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:13:26 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 15:40:03 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	get_exec_path(t_ctx *ctx, t_str *exec)
{
	t_lst	*elm;
	t_str	exec_path;

	printf("here\n");
	elm = ctx->paths;
	//*(curr_group()) = TMP_ALLOC;
	while (elm)
	{
		new_str(&exec_path, elm->data.len + exec->len, PARS_ALLOC);
		merge(&exec_path, &elm->data, exec, '/');
		if (!access(exec_path.str, X_OK))
		{
			xfree(exec->str, PARS_ALLOC);
			*exec = exec_path;
			return (NO_ERROR);
		}
		xfree(exec_path.str, TMP_ALLOC);
		elm = elm->next;
	}
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

t_err	get_exec_arg(char ***arg, t_token *parse)
{
	t_token		*elm;
	int			size;
	int			x;

	size = 0;
	elm = parse;
	while (elm && ++size)
		elm = elm->next;
	if (xmalloc(arg, (size + 1) * sizeof(char *), TMP_ALLOC))
		return (MEMORY_ERROR);
	elm = parse;
	x = 0;
	while (elm)
	{
		(*arg)[x] = elm->value.str;
		elm = elm->next;
	}
	return (NO_ERROR);
}
