/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_handshake_client.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 22:40:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 02:33:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	handshake(pid_t server)
{
	int	sec_remaining;

	setup_sigaction(SIG_HANDSHAKE, handle_handshake);
	setup_sigaction(SIG_MSG_RECEIVED, msg_received);
	if (kill(server, SIG_HANDSHAKE) == -1)
	{
		ft_printf("Could not reach a server with PID %d.\n", server);
		exit (KILL_ERROR);
	}
	sec_remaining = sleep(TIMEOUT_SEC);
	if (g_stage != LEN_TRANSMISSION_STAGE && sec_remaining == 0)
		timeout(server, TIMEOUT_SEC);
}

void	handle_handshake(int signo, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signo == SIG_HANDSHAKE)
		g_stage = LEN_TRANSMISSION_STAGE;
}
