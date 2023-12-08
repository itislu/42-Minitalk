/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_handshake_stage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:04:57 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 02:27:45 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	handshake(siginfo_t *info, int stage[])
{
	if (signo == SIG_HANDSHAKE)
	{
		stage[info->si_pid] = GET_LEN_STAGE;
		if (kill(info->si_pid, SIG_HANDSHAKE) == -1)
			exit (KILL_ERROR);
	}
	else
		if (kill(info->si_pid, SIG_HANDSHAKE_ERROR) == -1)
			exit (KILL_ERROR);
}
