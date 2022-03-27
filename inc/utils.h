/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:46:16 by artblin           #+#    #+#             */
/*   Updated: 2022/03/27 21:15:19 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <struct.h>

t_err	merge(t_str *dest, char *str1, const char *str2);
t_err	compare(const char *what, const char *with);
t_err	split_arr(char ***array, const char *str, const char del, const int alloc_group);
t_err	split_lst_normal(t_lst **head, const char *str,  const char sep, const int alloc_group);
t_err	split_lst_inverted(t_lst **head, const char *str,  const char sep, const int alloc_group);

#endif
