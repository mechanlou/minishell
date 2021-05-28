/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:24:11 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/10 13:16:37 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_double_semicolon(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
	{
		if (str[i] == ';' && str[i + 1] == ';')
			return (1);
		i++;
	}
	return (0);
}

int	get_nb_semicolons(char *line)
{
	int		i;
	int		nb_semicolons;
	bool	open_single;
	bool	open_double;

	i = 0;
	nb_semicolons = 0;
	open_double = false;
	open_single = false;
	while (line[i])
	{
		if (line[i] == '\'' && !open_double)
			open_single = !open_single;
		else if (line[i] == '\"' && !open_single)
			open_double = !open_double;
		else if (line[i] == ';')
			nb_semicolons++;
		i++;
	}
	return (nb_semicolons);
}

char	**fill_split_semicolons(char *line, char **strs)
{
	int		i;
	int		j;
	int		previous;

	previous = 0;
	i = 0;
	j = 0;
	while (previous < (int)ft_strlen(line))
	{
		while ((line[i] && (line[i] != ';' || is_inside_quotes(line, i))))
			i++;
		strs[j] = ft_strndup(line + previous, i - previous);
		if (!strs[j])
		{
			free_split(strs);
			return (NULL);
		}
		j++;
		while (line[i] == ';')
			i++;
		previous = i;
	}
	strs[j] = NULL;
	return (strs);
}

char	**split_semicolons(char *line)
{
	int		i;
	char	**strs;

	if (check_double_semicolon(line))
		return (NULL);
	strs = malloc(sizeof(char *) * (get_nb_semicolons(line) + 2));
	if (!strs)
		return (NULL);
	strs = fill_split_semicolons(line, strs);
	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i])
	{
		if (is_str_empty(strs[i]))
		{
			free_split(strs);
			return (NULL);
		}
		i++;
	}
	return (strs);
}