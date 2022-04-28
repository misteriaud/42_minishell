/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:26:34 by artblin           #+#    #+#             */
/*   Updated: 2022/04/27 17:08:05 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_unset(t_ctx *ctx, t_token *args)
{
	(void)ctx;
	(void)args;
	printf("unset\n");
	return (NO_ERROR);
	//exit(NO_ERROR);
}
