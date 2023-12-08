/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_handshake.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:40:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 12:15:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	handshake(pid_t pid_server)
{
	int					sec_remaining;

	setup_sigaction(SIG_HANDSHAKE, handle_handshake);
	setup_sigaction(SIG_SERVER_ERROR, server_error);
	if (kill(pid_server, SIG_HANDSHAKE) == -1)
	{
		ft_printf("Could not reach a server with PID %d.\n", pid_server);
		exit (KILL_ERROR);
	}
	sec_remaining = sleep(TIMEOUT_SEC);
	if (g_stage != GET_LEN_STAGE && sec_remaining == 0)
		timeout(pid_server, TIMEOUT_SEC);
}

void	handle_handshake(int signo, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signo == SIG_HANDSHAKE)
		g_stage = GET_LEN_STAGE;
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
