/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_buffer_msg_stage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:20 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 01:32:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	buffer_msg(size_t *len, int signo, pid_t pid)
{
	static int	bit[MAX_PID];
	static int	byte[MAX_PID];

	if (!g_msg[pid])
	{
		g_msg[pid] = (char *) malloc(*len * sizeof(char));
		if (!g_msg[pid])
			free_all_and_exit(g_msg, MALLOC_ERROR);
	}
	set_bit(&g_msg[pid][byte[pid]]);
	if (++bit[pid] == 8)
	{
		bit[pid] = 0;
		if (++byte[pid] == *len)
		{
			g_msg[pid][byte[pid]] = '\0';
			byte[pid] = 0;
			*len = 0;
			return (DISPLAY_MSG_STAGE);
		}
	}
	else
		g_msg[pid][byte[pid]] <<= 1;
	return (BUFFER_MSG_STAGE);
}

/* Alternative */
// #define SET_BIT(byte, signo) \
//     do { \
//         if (signo == SIG_ONE) \
//             *(byte) |= 0b1; \
//         else \
//             *(byte) &= ~0b1; \
//     } while (0)
