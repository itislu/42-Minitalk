/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_buffer_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:20 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 13:49:27 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	buffer_msg(size_t *len, int signo, pid_t client)
{
	static int		bit[MAX_PID];
	static size_t	byte[MAX_PID];
	static size_t	mask[MAX_PID];

	if (!g_msg[client])
	{
		g_msg[client] = calloc_msg(*len);
		mask[client] = 0b1;
	}
	if (signo == SIG_ONE)
		g_msg[client][byte[client]] |= mask[client];
	if (++bit[client] == 8)
	{
		mask[client] = 0b1;
		bit[client] = 0;
		if (++byte[client] == *len)
		{
			byte[client] = 0;
			*len = 0;
			return (DISPLAY_MSG_STAGE);
		}
	}
	else
		mask[client] <<= 1;
	return (MSG_TRANSMISSION_STAGE);
}
