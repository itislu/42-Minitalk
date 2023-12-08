/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:18:54 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 02:24:19 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	save_in_static(void *data, void (*func)(int, siginfo_t *, void *))
{
	func(0, NULL, data);
}

void	server_error(int signo, siginfo_t *info, void *context)
{
	exit(SERVER_ERROR);
}

void	setup_sigaction(int signal, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit (SIGEMPTYSET_ERROR);
	if (sigaction(signal, &sa, NULL) == -1)
		exit (SIGACTION_ERROR);
}

void	transmit_bit(size_t *c, int *bit, pid_t pid)
{
	if (*c & 0b10000000)
	{
		if (kill(pid, SIG_ONE) == -1)
			exit (KILL_ERROR);
	}
	else
		if (kill(pid, SIG_ZERO) == -1)
			exit (KILL_ERROR);
	*c <<= 1;
	(*bit)++;
}

void	wait_for_server(size_t bytes_to_send)
{
	int					bytes_sent;
	int					bits_sent;

	bytes_sent = 0;
	while (bytes_sent < bytes_to_send)
	{
		bits_sent = 0;
		while (bits_sent < 8)
		{
			if (pause() == -1 && errno != EINTR)
				exit (PAUSE_ERROR);
			bits_sent++;
		}
		bytes_sent++;
	}
}
