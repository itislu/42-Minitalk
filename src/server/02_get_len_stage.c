/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_get_len_stage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:47:01 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 01:32:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

int	get_len(size_t *len, int signo, pid_t pid)
{
	static int	bit[MAX_PID];
	static int	lensize[MAX_PID];

	if (!lensize[pid])
	{
		lensize[pid] = get_lentype(signo);
	}
	else
	{
		if (signo == SIG_ONE)
			*len |= 0b1;
		else
			*len &= ~0b0;
		if (++bit[pid] == lensize[pid])
		{
			bit[pid] = 0;
			lensize[pid] = 0;
			usleep(100);	// Might be needed for client to switch handler to send_msg
			return (BUFFER_MSG_STAGE);
		}
		else
			*len <<= 1;
	}
	return (GET_LEN_STAGE);
}

int	get_lentype(int signo)
{
	if (signo == SIG_INT)
		return (sizeof(unsigned int));
	else if (signo == SIG_LONG)
		return (sizeof(size_t));
}
