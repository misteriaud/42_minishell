/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 23:40:40 by artblin           #+#    #+#             */
/*   Updated: 2022/03/26 23:41:44 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM_H
# define TERM_H

# include <struct.h>

void	init_term(t_ctx *ctx);
void	set_raw_term(t_ctx *ctx);
void	set_origin_term(t_ctx *ctx);

#endif
