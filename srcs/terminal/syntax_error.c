/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 15:02:57 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/02 15:16:13 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "libft_string.h"
#include "syntax_error.h"

/*
** Check si la ligne est vide
** Return [int] 1 - Success
** Return [int] 0 - Failed
*/

static int	check_empty_line(char *input)
{
	int i;

	i = 0;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (!input[i])
		return (1);
	return (0);
}

/*
** Verifie le dernier caractère et agis en fonction.
** Return [char] 3 - Error, call new command
** Return [char] 2 - Call new line
** Return [char] 0 - To execute
*/

static char	check_end_line(char *input, int type, int flagantislash)
{
	int i;

	if (flagantislash)
		return (NEW_LINE);
	else if (type == OPERAT)
	{
		i = 0;
		while (input[i])
			i++;
		i--;
		while (ft_memchr("\t\n ", input[i], 3))
			i--;
		if (input[i] == ';')
			return (TO_EXECUTE);
		return (NEW_LINE);
	}
	else if (type == REDIRECT)
		return (NCMD_SYNTAX_ERROR);
	return (TO_EXECUTE);
}

/*
** first set of conditions, check parenthesis and operators with 2 char
*/

short		condition_synt_err1(char *input, int *i, int *type)
{
	short	return_value;

	if (input[*i] == ')')
		return (NCMD_SYNTAX_ERROR);
	else if (input[*i] == '(')
	{
		if ((return_value = syntax_parenth(input + *i, *type, i)))
			return (return_value);
		*type = PARENTH;
	}
	else if (!ft_strncmp(">>", input + *i, 2)
			|| !ft_strncmp("&&", input + *i, 2)
			|| !ft_strncmp("||", input + *i, 2))
	{
		if (*type == OPERAT || *type == REDIRECT)
			return (NCMD_SYNTAX_ERROR);
		*type = (!ft_strncmp(">>", input + *i, 2)) ? REDIRECT : OPERAT;
		*i += 2;
	}
	return (0);
}

/*
** second set of conditions, check operators with 1 char,
** quotes, blanks and words
*/

short		condition_synt_err2(char *input, int *i, int *type)
{
	if (ft_memchr("<>|;", input[*i], 4))
	{
		if (*type == OPERAT || *type == REDIRECT)
			return (NCMD_SYNTAX_ERROR);
		type = (ft_memchr("<>", input[*i], 2)) ? REDIRECT : OPERAT;
		*i += 1;
	}
	else if (ft_memchr("\'\"", input[*i], 2))
	{
		if (pass_quotes(input, i))
			return (NCMD_SYNTAX_ERROR);
		*type = WORD;
		*i += 1;
	}
	else if (ft_memchr(" \t\n", input[*i], 3))
		pass_blank(input, i);
	else
	{
		if (*type == PARENTH)
			return (NCMD_SYNTAX_ERROR);
		*type = WORD;
		*i += 1;
	}
	return (0);
}

/*
** Verifie la syntaxe de la commande
** Return [short] 0 - Can be executed
** Return [short] 1 - Error malloc
** Return [short] 2 - Add a new line
** Return [short] 3 - Ask a new command
** Return [short] 4 - Syntax error. New command
** Type : 0 Word, 1 Operator, 2 Parenthesis, 3 redirection
*/

short		syntax_error(char *input, int flagantislash)
{
	int		i;
	int		type;
	short	return_value;

	i = 0;
	type = OPERAT;
	if (check_empty_line(input))
		return (NEW_COMMAND);
	while (input[i])
	{
		if (return_value = condition_synt_err1(input, &i, &type))
			return (return_value);
		else
		{
			if (return_value = condition_synt_err2(input, &i, &type))
				return (return_value);
		}
	}
	return (check_end_line(input, type, flagantislash));
}
