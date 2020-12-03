/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:22:44 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/03 17:01:19 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft_mem.h"
# include "libft_string.h"
# include "sh_utils.h"
# include <stdlib.h>

#define VAR_AMBIGUOUS	2
#define VAR_VALID 		1
#define VAR_NONE  		0

/*
**  EXPANDERS
*/
int		expand_var(char **dst, const char *str);
int     expand_word(t_cmd **dst, char *str);
int		expand_quotes(t_cmd *src);
int     expand_bslash(t_cmd *src);

int     expand_cmd(t_cmd **dst, char *simple_command);

#endif