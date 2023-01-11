/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibernot <tibernot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:50:34 by tibernot          #+#    #+#             */
/*   Updated: 2023/01/11 14:20:19 by tibernot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_in(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	while_till(char *str, int i, char c)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != c)
		j++;
	return (j);
}

t_list	*create_heredocs(char *str)
{
	int		i;
	int		j;
	t_list	*lst;

	lst = NULL;
	i = 0;
	while (str[++i])
	{
		j = 0;
		if (str[i] == '<' && str[i - 1] == '<')
		{
			i++;
			while (str[i] && is_in(str[i], " \f\n\t\v\r"))
				i++;
			if (!str[i])
				return (NULL);
			if ((str[i] == '\"') || (str[i] == '\"'))
				j = while_till(str, i, str[i]);
			else
				j = while_till(str, i, ' ');
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, j)));
			i = i + j;
		}
	}
	return (lst);
}

int	good_heredocs(char	*str, t_list *hd)
{
	int		nb_hd;
	int		i;
	t_list	*tmp;

	tmp = hd;
	nb_hd = 0;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		nb_hd++;
	}
	while (str[++i])
	{
		if (str[
			i] == '<' && str[i - 1] == '<')
		nb_hd--;
	}
	if (nb_hd != 0)
		return (0);
	return (1);
}

void	do_heredoc(char *hd_out)
{
	char	*line;

	line = readline("> ");
	while (ft_strncmp(hd_out, line, ft_strlen(line)) != 0)
		line = readline("> ");
}

void	do_heredocs(char *str)
{
	t_list	*heredocs;
	t_list	*tmp;

	heredocs = create_heredocs(str);
	if (!good_heredocs(str, heredocs))
		ft_lstclear(&heredocs, free);
	tmp = heredocs;
	while (tmp)
	{
		do_heredoc(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&heredocs, free);

}
