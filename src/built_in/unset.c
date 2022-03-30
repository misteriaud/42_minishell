/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:26:34 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 15:31:27 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cmd_unset(t_ctx *ctx, t_token *args)
{
	(void)ctx;
	(void)args;
	printf("unset\n");
	exit(NO_ERROR);
}
