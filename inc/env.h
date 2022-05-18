/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 22:33:16 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 16:15:38 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <struct.h>

# define ENV_GROUP	0

t_err	add_to_env(t_ctx *ctx, char *key, int assign, char *value);

t_err	expand_path(t_ctx *ctx, t_str *path);

t_err	init_env(t_ctx *ctx, char **env);

t_err	print_env(t_ctx *ctx);

t_err	refresh_paths(t_ctx *ctx);

// get value of variable
t_err	get_variable(t_ctx *ctx, const char *key, t_str *value);

t_err	get_address_variable(t_ctx *ctx, const char *key,
			t_str **address_value);

// test and get execution path
t_err	get_exec_path(t_ctx *ctx, t_str *exec);

// replace variable key by value in string
t_err	drop_variables(t_ctx *ctx, t_str *parse);

t_err	alloc_node(t_lst ***elm, int *global_len, t_str *tmp);

t_err	create_var_node(t_ctx *ctx, char **str, t_lst ***elm, int *global_len);

t_err	create_text_node(char **str, t_lst ***elm,
			int *global_len, const char sep);

t_err	create_dollar_node(t_lst ***elm, int *global_len);

t_err	get_exec_arg(char ***arg, t_token *parse);
// duplicate variable environment list to array
t_err	package_env(t_ctx *ctx);

#endif
