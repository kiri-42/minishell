/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar <tkirihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 23:42:51 by tkirihar          #+#    #+#             */
/*   Updated: 2022/03/25 15:34:54 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "repl.h"
#include "sigaction.h"
#include "common.h"

int	g_exit_status = 0;

int	main(void)
{
	set_signal_handler_during_command();
	start_repl();
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q minishell");
// }
