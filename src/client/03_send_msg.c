/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_send_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:21:49 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 13:41:13 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_msg(int signo, siginfo_t *info, void *context)
{
	static int	bit;
	static char	*msg;

	if (!signo && !msg)
		msg = (char *) context;
	else if (signo == SIG_SERVER_READY && msg)
	{
		if (bit == 8)
		{
			msg++;
			bit = 0;
		}
		transmit_bit(*msg, &bit, info->si_pid);
	}
}
