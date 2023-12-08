/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_handshake_server.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:04:57 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 15:48:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handshake(int signo, pid_t pid_client, int stage[])
{
	if (signo == SIG_HANDSHAKE)
	{
		stage[pid_client] = COMM_LEN_STAGE;
		if (kill(pid_client, SIG_HANDSHAKE) == -1)
			exit (KILL_ERROR);
	}
	else
		if (kill(pid_client, SIG_HANDSHAKE_ERROR) == -1)
			exit (KILL_ERROR);
}
