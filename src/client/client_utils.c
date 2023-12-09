/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:18:54 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 04:30:47 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	save_in_static(void *data, void (*func)(int, siginfo_t *, void *))
{
	func(0, NULL, data);
}

void	msg_received(int signo, siginfo_t *info, void *context)
{
	(void) signo;
	(void) context;
	ft_printf("Message to server %d successfully transmitted.\n", info->si_pid);
	exit(SUCCESS);
}

void	setup_sigaction(int signal, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit (SIGEMPTYSET_ERROR);
	if (sigaction(signal, &sa, NULL) == -1)
		exit (SIGACTION_ERROR);
}

void	timeout(pid_t server, int timeout_sec)
{
	ft_printf("Server with PID %d did not respond in %d seconds.\n",
		server, timeout_sec);
	exit (TIMEOUT_ERROR);
}
