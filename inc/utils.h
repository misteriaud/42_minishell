/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 13:46:16 by artblin           #+#    #+#             */
/*   Updated: 2022/05/20 14:16:59 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <struct.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

char	*ft_itoa(int i);

t_err	str_dup(char **new, const char *str, int alloc);

char	*str_join(const char *left, const char *right, const int alloc);

int		get_len(const char *str);

t_err	byte_count(const char *str, int *nbr_byte, const char sep);

t_err	token_count(const char *str, int *nbr_token, const char sep);

t_err	new_str(t_str *data, const int len, const int alloc_group);

t_err	str_fill(t_str *dst, const char *str);

t_err	str_fill_from_lst(t_str *out, t_lst *lst);

t_err	merge(t_str *merged, t_str *left, t_str *right, const char sep);

t_err	compare(const char *what, const char *with);

t_err	split_arr(char ***array, const char *str,
			const char del, const int alloc_group);

t_err	split_lst_normal(t_lst **head, const char *str,
			const char sep, const int alloc_group);

t_err	split_lst_inverted(t_lst **head, const char *str,
			const char sep, const int alloc_group);

t_bool	is_set(const char c, const char *set);

t_bool	is_containing_set(const char *str, const char *set);
t_bool	is_only_set(const char *str, const char *set);

int		is_num(const char c);
int		is_lower(const char c);
int		is_upper(const char c);
int		is_under(const char c);
int		is_variable(const char c);
int		is_var_start(const char c);
int		is_white(const char c);

void	print_custom_err(const char *str);
t_err	print_err(t_err err, char *str);
int		secure_atoi(char *str, long *result);
t_err	is_dir(const char *path);
t_err	is_reg(const char *path);
void	close_fds(int fds);
void	close_all(int i);
t_bool	is_empty_str(char *str);
t_err	writer(int fd, char *str, unsigned int size);

#endif
