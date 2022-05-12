/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 15:54:07 by artblin           #+#    #+#             */
/*   Updated: 2022/05/12 16:00:06 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
#define WILDCARD_H

#include <dirent.h>
#include <stddef.h>
#include <stdio.h>

typedef struct dirent		t_entity;
typedef DIR					t_dir;

void	expand_wildcard(const char *directory);

#endif
