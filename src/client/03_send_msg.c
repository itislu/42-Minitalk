/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_send_msg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 02:21:49 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 14:54:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	send_msg(int signo, siginfo_t *info, void *context)
{
	static size_t	c;
	static int		bit;
	static char		*msg;

	if (!signo && !msg)
		msg = (char *) context;
	else if (signo == SIG_SERVER_READY)
	{
		if (bit == 8)
			if (*++msg)
				bit = 0;
		if (bit == 0)
			c = *msg;
		if (msg && *msg)
			transmit_bit(&c, &bit, info->si_pid);
		else
		{
			if (bit != 0)
				ft_printf("Message transmitted successfully.\n");
			else
				ft_printf("Message was empty, no need to transmit.\n");
		}
	}
}
