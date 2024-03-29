/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alboudje@student.42lyon.fr <alboudje>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:37:57 by alboudje          #+#    #+#             */
/*   Updated: 2023/02/06 13:18:28 by alboudje@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execution.h"

int	is_builtins(t_command *cmd)
{
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (1);
	return (0);
}

int	run_builtin(t_command **cmds, t_env_var **vars)
{
	int	temp;
	int	result;

	temp = dup(1);
	dup2((*cmds)->fd_out, STDOUT_FILENO);
	if (!ft_strcmp((*cmds)->cmd, "pwd"))
		result = ft_pwd();
	if (!ft_strcmp((*cmds)->cmd, "cd"))
		result = ft_cd((*cmds)->args + 1,
				arg_size((*cmds)->args + 1), *vars);
	if (!ft_strcmp((*cmds)->cmd, "echo"))
		result = ft_echo((*cmds)->args + 1,
				arg_size((*cmds)->args + 1));
	if (!ft_strcmp((*cmds)->cmd, "export"))
		result = ft_export((*cmds)->args, vars);
	if (!ft_strcmp((*cmds)->cmd, "unset"))
		result = ft_unset((*cmds)->args, vars);
	if (!ft_strcmp((*cmds)->cmd, "env"))
		result = ft_env(*vars);
	if (!ft_strcmp((*cmds)->cmd, "exit"))
		result = ft_exit((*cmds)->args + 1,
				arg_size((*cmds)->args) - 1, vars);
	dup2(temp, STDOUT_FILENO);
	rm_command(cmds);
	return (close(temp), result);
}

void	run_everything(t_command **cmds, t_env_var **vars)
{
	int	*pids;

	pids = malloc(sizeof(int) * size_commands(*cmds));
	if (!pids)
		return ((void)ft_putstr_fd("malloc error\n", 2));
	if (!cmds)
		return ;
	if (size_commands(*cmds) == 1 && is_builtins(*cmds))
		run_builtin(cmds, vars);
	else if (size_commands(*cmds))
		run_cmds(cmds, vars, pids);
	free(pids);
}

int	arg_size(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	exit_all_fork_broken(int pipe_fd[2][2],
	int size, int *pids, t_command **cmds_list)
{
	multi_close(pipe_fd[0], pipe_fd[1]);
	while (*cmds_list)
		rm_command(cmds_list);
	wait_cmds(size, pids);
	return (1);
}
