/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:24:56 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 16:37:04 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_err	swap_pwd(t_ctx *ctx)
{
	t_str	*pwd;
	char	*tmp;
	t_str	*oldpwd;

	if (get_address_variable(ctx, "PWD", &pwd))
	{
		add_to_env(ctx, "PWD", 2, NULL);
		get_address_variable(ctx, "PWD", &pwd);
	}
	if (get_address_variable(ctx, "OLDPWD", &oldpwd))
	{
		add_to_env(ctx, "OLDPWD", 2, NULL);
		get_address_variable(ctx, "OLDPWD", &oldpwd);
	}
	xfree(oldpwd->str, ENV_ALLOC);
	oldpwd->str = pwd->str;
	oldpwd->len = pwd->len;
	tmp = getcwd(NULL, 0);
	str_dup(&pwd->str, tmp, ENV_ALLOC);
	free(tmp);
	pwd->len = get_len(pwd->str);
	return (NO_ERROR);
}

static t_err	check_and_change_path(t_str *path)
{
	if (access(path->str, F_OK)
		|| chdir(path->str))
		return (perror(path->str), UNKNOWN_PATH_ERROR);
	return (NO_ERROR);
}

t_err	cmd_cd(t_ctx *ctx, t_token *args)
{
	t_str	*home;
	t_err	err;

	if (!args)
	{
		err = get_address_variable(ctx, "HOME", &home);
		if (err)
			return (err);
		err = check_and_change_path(home);
		if (err)
			return (err);
	}
	else
	{
		expand_path(ctx, &args->value);
		err = check_and_change_path(&args->value);
		if (err)
			return (err);
	}
	swap_pwd(ctx);
	return (NO_ERROR);
}
