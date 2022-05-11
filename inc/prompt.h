/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:35:47 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/11 09:36:08 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include <struct.h>
# include <env.h>
# include <unistd.h>
# include <utils.h>

t_err	get_prompt(char **data, const unsigned int old_status);

#endif
