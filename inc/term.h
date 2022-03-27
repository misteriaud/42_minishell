/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:40:40 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 21:09:45 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <struct.h>
# include <sys/ioctl.h>
# include <unistd.h>

void	init_term(t_ctx *ctx);
void	set_raw_term(t_ctx *ctx);
void	set_origin_term(t_ctx *ctx);
t_err	get_cols(int *cols);

#endif
