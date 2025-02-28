/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handler_during_command.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:29:19 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 16:48:06 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"

/* SIGINT */
static void	handle_sigint_during_command(int sig)
{
	printf("\n");
	g_exit_status = 128 + sig;
}

static void	set_sigint_handler_during_command(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint_during_command;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

/* SIGQUIT */
static void	handle_sigquit_during_command(int sig)
{
	printf("Quit: 3\n");
	g_exit_status = 128 + sig;
}

static void	set_sigquit_handler_during_command(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigquit_during_command;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT, &act, NULL);
}

void	set_signal_handler_during_command(void)
{
	set_sigint_handler_during_command();
	set_sigquit_handler_during_command();
}
