/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_handshake.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:40:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 02:25:41 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

bool	handshake(pid_t pid_server)
{
	struct sigaction	sa;

	sa.sa_handler = handle_handshake;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit (SIGEMPTYSET_ERROR);
	if (sigaction(SIG_HANDSHAKE, &sa, NULL) == -1)
		exit (SIGACTION_ERROR);
	if (kill(pid_server, SIG_HANDSHAKE) == -1)
	{
		ft_printf("Could not reach a server with PID %d.\n", pid_server);
		exit (KILL_ERROR);
	}
	if (pause() == -1 && errno != EINTR)
		exit (PAUSE_ERROR);
	if (g_state != /* NEXT_STATE */)
		exit ();
	setup_sigaction(SIG_SERVER_ERROR, server_error);
	// reset_sigusr1(&sa);
	return (g_state);
}

void	handle_handshake(int signo)
{
	if (signo == SIG_HANDSHAKE)
		g_state = /* NEXT_STATE */;
}

// void	reset_sigusr1(struct sigaction *sa)	//Change to indicate any kind of error or finish state from server to exit
// {
// 	sa->sa_handler = exit;
// 	sa->sa_flags = 0;
// 	if (sigemptyset(&sa->sa_mask) == -1)
// 		exit (SIGEMPTYSET_ERROR);
// 	if (sigaction(SIG_EXIT, sa, NULL) == -1)
// 		exit (SIGACTION_ERROR);
// }
