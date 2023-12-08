/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_get_len_stage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:47:01 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 14:42:32 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

int	get_len(size_t *len, int signo, pid_t pid_client)
{
	static int		bit[MAX_PID];
	static int		lensize[MAX_PID];
	static size_t	mask[MAX_PID];

	if (!lensize[pid_client])
	{
		lensize[pid_client] = get_lentype(signo);
		mask[pid_client] = 0b1;
		*len = 0;
	}
	else
	{
		if (signo == SIG_ONE)
			*len |= mask[pid_client];
		if (++bit[pid_client] == lensize[pid_client])
		{
			bit[pid_client] = 0;
			lensize[pid_client] = 0;
			usleep(100);	// Might be needed for client to switch handler to send_msg
			return (BUFFER_MSG_STAGE);
		}
		else
			mask[pid_client] <<= 1;
	}
	return (GET_LEN_STAGE);
}

int	get_lentype(int signo)
{
	if (signo == SIG_INT)
		return (sizeof(unsigned int));
	else
		return (sizeof(size_t));
}
