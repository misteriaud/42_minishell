/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:24:56 by artblin           #+#    #+#             */
/*   Updated: 2022/04/28 14:19:05 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


t_err	cmd_cd(t_ctx *ctx, t_token *args)
{
	t_str	*new_path;

	if (!args)
	{
		write(1, "need path\n", 14);
		return (ARG_ERROR);
	}
	if (!args->value.str)
		return (NULL_PTR_ERROR);
	if (chdir(args->value.str))
	{
		write(1, "invalide path\n", 14);
		return (UNKNOWN_PATH_ERROR);
	}

	get_address_variable(ctx, "PWD", &new_path);

	xfree(new_path->str, ENV_ALLOC);

	new_str(new_path, args->value.len, ENV_ALLOC);
	str_fill(new_path, args->value.str);

		char *pwd = getcwd(NULL, 0);
		printf("pwd::%s\n\n", pwd);


	return (NO_ERROR);
}
