/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handshake_server.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:04:57 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 23:19:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

extern volatile sig_atomic_t	g_is_handshake_success[];

void	handshake(siginfo_t *info)
{
	g_is_handshake_success[info->si_pid] = true;
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit (KILL_ERROR);
	if (usleep(100) == -1)
		exit (USLEEP_ERROR);
}
