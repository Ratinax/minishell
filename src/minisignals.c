/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisignals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 11:26:31 by alboudje          #+#    #+#             */
/*   Updated: 2023/01/27 16:02:37 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_err = 1;
}

void	sigquit_process(int sig)
{
	(void)sig;
	ft_putstr_fd("Quit: 3\n", 2);
	g_err = 131;
}

void	sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
	g_err = 1;
}

void	intquit(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 2);
	g_err = 130;
}
