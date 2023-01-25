/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:36:36 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/25 15:11:05 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "builtins.h"

t_env_var	*init_cmds(char **envp)
{
	int			i;
	t_env_var	*vars;

	vars = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		ft_export(envp[i], &vars);
		i++;
	}
	return (vars);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		**hds;
	t_list		**all_cmds;
	t_env_var	*vars;
	t_command	*cmds;
	int			pt;

	pt = 0;
	cmds = NULL;
	(void) argc;
	(void) argv;
	vars = init_cmds(envp);
	line = "l";
	hds = NULL;
	while (line)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			while (vars)
				ft_unset(vars->name, &vars);
			return (clear_history(), free(line), 0);
		}
		if (line[0])
		{
			add_history(line);
			if (parsing_errors(line))
				ft_putendl_fd("Parsing error", 2);
			else
			{
				hds = do_heredocs(line); // do in a fork()
				all_cmds = get_all(line);
				to_good_cmds(all_cmds, &vars);
				cmds = create_commands(all_cmds, vars, hds);
				run_everything(&cmds, &vars, &pt);
				free_alist(all_cmds);
				free(line);
				free_all(hds);
			}
		}
	}
	return (0);
}
