/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:24:56 by artblin           #+#    #+#             */
/*   Updated: 2022/04/28 17:55:46 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_err swap_pwd(t_ctx *ctx)
{
	t_str	*pwd;
	t_str	*oldpwd;


	get_address_variable(ctx, "PWD", &pwd);
	get_address_variable(ctx, "OLDPWD", &oldpwd);

	xfree(oldpwd->str, ENV_ALLOC);
	oldpwd->str = pwd->str;
	oldpwd->len = pwd->len;

	pwd->str = getcwd(NULL, 0);
	pwd->len = get_len(pwd->str);
	//new_str(pwd, path->len, ENV_ALLOC);
	//str_fill(pwd, path->str);

	return (NO_ERROR);
}

static t_err check_and_change_path(t_str *path)
{
	if (access(path->str, F_OK)
		|| chdir(path->str))
	{
		perror(path->str);
		//write(STDOUT_FILENO, "Invalid path\n", 18);
		return (UNKNOWN_PATH_ERROR);
	}
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
		err = check_and_change_path(&args->value);
		if (err)
			return (err);
	}
	swap_pwd(ctx);
	return (NO_ERROR);
}
