/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_handshake_server.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:04:57 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 23:43:35 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handshake(int signo, pid_t client, int stage[])
{
	if (signo == SIG_HANDSHAKE)
	{
		stage[client] = LEN_TRANSMISSION_STAGE;
		if (kill(client, SIG_HANDSHAKE) == -1)
			client_not_reachable(client, stage);
	}
	else
		kill(client, SIG_HANDSHAKE_ERROR);
}
