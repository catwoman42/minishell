/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fatoudiallo <fatoudiallo@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:22:31 by fatdiall          #+#    #+#             */
/*   Updated: 2023/12/19 13:45:06 by fatoudiallo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_minishell(t_data *datas)
{
	printf("\nExit\n");
	// FREE ALL MALLOCS
	if (datas->prompt)
		free(datas->prompt);
	free_2d_char(datas->copy_env);
	close(datas->saved_fd_in);
	close(datas->saved_fd_out);
	free(datas->pwd);
	exit(0);
}

void	handlerctrlc(int num)
{
	(void)num;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Role des fonctions readlines.
// rl_on_new_line(); curseur sur une nouvelle ligne
// rl_replace_line("", 0); a partir de l'emplacement 0 = debut ligne, remplace la ligne par un ""
// rl_redisplay();re affiche l'input apres modifs

// function clears the current input line
// displays a new prompt on a new line
// and provides a clean interface to enter a new command.
