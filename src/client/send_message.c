/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:27:14 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 00:17:48 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	send_msg(pid_t pid, char *msg)
{
	unsigned char	c;
	int				i;

	ft_printf("pid: %d\n", pid);
	while (*msg)
	{
		c = *msg;
		i = 0;
		while (i++ < 8)
		{
			if (c & 0b10000000)
			{
				kill(pid, SIGUSR1);
				ft_printf("1: %d\n", i);
			}
			else
			{
				kill(pid, SIGUSR2);
				ft_printf("0: %d\n", i);
			}
			c <<= 1;
			usleep(50);
		}
		msg++;
	}
}
