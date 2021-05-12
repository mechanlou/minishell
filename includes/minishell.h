/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:38:25 by rkowalsk          #+#    #+#             */
/*   Updated: 2021/05/12 14:36:38 by rkowalsk         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <stdbool.h>
# include <sys/types.h>
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

# define DEL_RIGHT 2117294875
# define DEL_LEFT 127
# define ARROW_UP 4283163
# define ARROW_DOWN 4348699
# define ARROW_LEFT 4479771
# define ARROW_RIGHT 4414235
# define CTRL_D 4
# define KEY_DLE 16
# define KEY_HOME 4741915
# define KEY_END 4610843

typedef struct s_pipe
{
	int			saved_in;
	int			saved_out;
}				t_pipe;

typedef struct s_curs_pos
{
	unsigned int	line_pos;
	unsigned int	path_size;
}				t_curs_pos;

typedef struct s_history
{
	char				*line;
	struct s_history	*previous;
	struct s_history	*next;
}				t_history;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			visible;
	struct s_env	*next;
}				t_env;

char		*env_get_value(char *name, t_env *list);
void		set_visible(char *name, t_env *list);
void		set_invisible(char *name, t_env *list);
void		print_list_visible_only(t_env *list);
void		env_print_list(t_env *list);
t_env		*env_add_link(char *name, char *value, bool visible, t_env *next);
t_env		*env_delete_link(t_env *list, char *name);
void		env_free_list(t_env *list);
int			error_ret_0(char *error);
int			success_ret(char *str, t_env *e, struct termios sav, t_history *h);
int			error_ret(char *str, t_env *e, struct termios sav, t_history *h);
int			free_split(char **str);
int			proceed_cmd(char **line, t_env **env_list);
int			cmd_execve(char **cmd, t_env *env_list);
int			cmd_cd(char **cmd);
int			cmd_echo(char **cmd);
int			cmd_pwd(char **cmd);
int			cmd_env(char **cmd, t_env *environ);
int			cmd_export(char **cmd, t_env *list);
int			cmd_unset(char **cmd, t_env **list);
int			pars_line(char *line, t_env **env_list);
char		**split_semicolons(char *line);
int			free_split_ret_error(char **split);
int			free_split_perror_ret_0(char **split);
char		*replace_vars(char *line, t_env *list);
char		**create_env_tab(t_env *list);
int			env_change_value(char *name, char *value, t_env *list);
int			set_variable(char *command, t_env **list);
void		reset_input_mode(struct termios saved_attributes);
char		*get_line(int path_size, t_history **list);
t_env		*create_env_list(char **env_tab);
void		set_input_mode(struct termios *saved_attributes);
int			init_termcaps(void);
char		*delete_right(char *line, t_curs_pos *cursor);
char		*delete_left(char *line, t_curs_pos *cursor);
void		goto_endofline(t_curs_pos *cursor, char *line);
t_history	*history_add_link(t_history *next, char *line);
void		history_change_line(t_history *link, char *new_value);
void		history_free_list(t_history *list);
void		history_print_list(t_history *list);
char		*arrow_keys(char *line, int buff, t_curs_pos *curs, t_history **l);
void		key_left_right(char *line, int buffer, t_curs_pos *cursor);
t_history	*history_del_first_link(t_history *link);
bool		is_inside_quotes(char *line, int j);
int			split_pipes(char *line, char ***commands);
int			is_str_empty(char *str);
int			pipe_start(t_pipe *pip);
int			pipe_end(t_pipe pip);

#endif
