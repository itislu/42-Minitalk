/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handshake_client.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:40:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 01:54:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

extern volatile char	*g_msg;

bool	handshake(pid_t pid_server)
{
	struct sigaction	sa;

	sa.sa_handler = handle_handshake;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit (SIGEMPTYSET_ERROR);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (SIGACTION_ERROR);
	if (kill(pid_server, SIGUSR1) == -1)
	{
		ft_printf("Could not reach a server with PID %d.\n", pid_server);
		exit (KILL_ERROR);
	}
	if (pause() == -1 && errno != EINTR)
		exit (PAUSE_ERROR);
	reset_sigusr1(&sa);
	return (g_msg);
}

void	handle_handshake(int signo)
{
	if (signo != SIGUSR1)
		g_msg = NULL;
}

void	reset_sigusr1(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sa->sa_flags = 0;
	if (sigemptyset(&sa->sa_mask) == -1)
		exit (SIGEMPTYSET_ERROR);
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		exit (SIGACTION_ERROR);
}
