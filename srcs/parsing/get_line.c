/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:42:28 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/21 20:02:59 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	goto_endofline(t_curs_pos *cursor, char *line)
{
	int	size;

	size = ft_strlen(line);
	while ((int)cursor->line_pos < size)
		key_left_right(line, ARROW_RIGHT, cursor);
}

char	*ret_exit(void)
{
	write(1, "\n", 1);
	return (ft_strdup("exit"));
}

char	*read_loop(t_curs_pos curs, char *line, t_history **hist, int *buffer)
{
	t_history	*curr_hist;
	int			ret;

	curr_hist = *hist;
	while (*buffer != '\n')
	{
		if (!line)
			return (NULL);
		*buffer = 0;
		ret = read(0, &*buffer, 4);
		if (ret < 0)
			return (NULL);
		else if (*buffer == CTRL_D)
			return (ret_exit());
		else if (*buffer == DEL_RIGHT)
			line = delete_right(line, &curs);
		else if (*buffer >= 4283163 || *buffer == KEY_DLE)
			line = arrow_keys(line, *buffer, &curs, &curr_hist);
		else if (*buffer == DEL_LEFT)
			line = delete_left(line, &curs);
		else if (*buffer > 31 && *buffer < 127 && *buffer != '\n')
			line = add_char(line, *buffer, &curs);
		(*hist)->line = line;
	}
	return (line);
}

char	*get_line(int path_size, t_history **history)
{
	t_curs_pos	cursor;
	char		*line;
	int			buffer;

	buffer = 0;
	cursor.line_pos = 0;
	cursor.path_size = path_size;
	line = ft_strdup("");
	*history = history_add_link(*history, line);
	if (!*history)
		return (NULL);
	line = read_loop(cursor, line, history, &buffer);
	if (!line)
		return (NULL);
	goto_endofline(&cursor, line);
	write(1, &buffer, 1);
	if (!ft_strlen(line))
		*history = history_del_first_link(*history);
	return (line);
}