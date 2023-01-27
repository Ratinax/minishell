/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:13:25 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/27 16:06:35 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"

int	run_builtins(t_command *cmd, t_env_var **vars)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (exit(ft_pwd()), 1);
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (exit(ft_cd(cmd->args + 1,
					arg_size(cmd->args + 1), *vars)), 1);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (exit(ft_echo(cmd->args + 1,
					arg_size(cmd->args + 1))), 1);
	if (!ft_strcmp(cmd->cmd, "export"))
		return (exit(ft_export(cmd->args, vars)), 1);
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (exit(ft_unset(cmd->args, vars)), 1);
	if (!ft_strcmp(cmd->cmd, "env"))
		return (exit(ft_env(*vars)), 1);
	return (0);
}

void	multi_close(int p1[2], int p2[2])
{
	close(p1[0]);
	close(p1[1]);
	close(p2[0]);
	close(p2[1]);
}

int	get_process_return(int pid)
{
	int	ret;

	ret = 0;
	waitpid(pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	if (g_err == 130 || g_err == 131)
		return (ret);
	if (ret)
		g_err = ret;
	else
		g_err = 127;
	return (ret);
}

int	get_heredoc_fd(char *here)
{
	int	fd[2];

	pipe(fd);
	ft_putstr_fd(here, fd[1]);
	close(fd[1]);
	return (fd[0]);
}

void	good_error_message(char *str)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	g_err = 127;
}
