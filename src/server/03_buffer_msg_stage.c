/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_buffer_msg_stage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:25:20 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 12:04:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

int	buffer_msg(size_t *len, int signo, pid_t pid_client)
{
	static int		bit[MAX_PID];
	static size_t	byte[MAX_PID];

	if (!g_msg[pid_client])
	{
		g_msg[pid_client] = (char *) malloc(*len * sizeof(char));
		if (!g_msg[pid_client])
			free_all_and_exit(MALLOC_ERROR);
	}
	set_bit(&g_msg[pid_client][byte[pid_client]], signo);
	if (++bit[pid_client] == 8)
	{
		bit[pid_client] = 0;
		if (++byte[pid_client] == *len)
		{
			g_msg[pid_client][byte[pid_client]] = '\0';
			byte[pid_client] = 0;
			*len = 0;
			return (DISPLAY_MSG_STAGE);
		}
	}
	else
		g_msg[pid_client][byte[pid_client]] <<= 1;
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
