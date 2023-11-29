/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:27:14 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/29 13:34:00 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	send_msg(pid_t pid, char *msg)
{
	unsigned char	c;
	int				i;

	while (*msg)
	{
		c = *msg;
		i = 0;
		while (i++ < 8)
		{
			if (c & 0b1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			c >>= 1;
		}
		msg++;
	}
}
