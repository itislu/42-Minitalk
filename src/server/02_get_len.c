/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_get_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:47:01 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 15:29:16 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

int	get_len(size_t *len, int signo, pid_t client)
{
	static int		bit[MAX_PID];
	static int		lensize[MAX_PID];
	static size_t	mask[MAX_PID];

	if (!lensize[client])
	{
		lensize[client] = get_lentype(signo) * 8;
		mask[client] = 0b1;
		*len = 0;
	}
	else
	{
		if (signo == SIG_ONE)
			*len |= mask[client];
		if (++bit[client] == lensize[client])
		{
			usleep(50000);
			bit[client] = 0;
			lensize[client] = 0;
			return (MSG_TRANSMISSION_STAGE);
		}
		mask[client] <<= 1;
	}
	return (LEN_TRANSMISSION_STAGE);
}

int	get_lentype(int signo)
{
	if (signo == SIG_UINT)
		return (sizeof(unsigned int));
	else
		return (sizeof(size_t));
}
