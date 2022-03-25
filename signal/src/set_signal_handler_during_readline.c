/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handler_during_readline.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:29:27 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 19:47:06 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"

/* SIGINT */
void	handle_sigint_during_readline(int sig)
{
	(void)sig;
	g_exit_status = 1;
	ft_putstr_fd("\n", STDERR);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	set_sigint_handler_during_readline(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint_during_readline;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

static void	set_sigquit_handler_during_readline(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_handler_during_readline(void)
{
	set_sigint_handler_during_readline();
	set_sigquit_handler_during_readline();
}
