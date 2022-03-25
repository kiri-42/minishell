/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal_handler_during_heredoc.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:29:24 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/24 16:53:12 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sigaction.h"
#include <unistd.h>

void	handle_sigint_during_heredoc(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

static void	set_sigint_handler_during_heredoc(void)
{
	struct sigaction	act;

	act.sa_handler = handle_sigint_during_heredoc;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);
}

static void	set_sigquit_handler_during_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	set_signal_handler_during_heredoc(void)
{
	set_sigint_handler_during_heredoc();
	set_sigquit_handler_during_heredoc();
}
