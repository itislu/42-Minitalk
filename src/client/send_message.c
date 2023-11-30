/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:27:14 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 13:17:31 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	display_msg_test(int sig)
{
	static unsigned char	c;
	static int				i;
	static	int				bytes;

	if (sig == 1)
	{
		c += 0b1;
	}
	else if (sig == 0)
	{
		c += 0b0;
	}
	if (++i == 8)
	{
		++bytes;
		ft_printf("%d\n", bytes);
		//write(1, &c, 1);
		c = 0;
		i = 0;
	}
	else
		c <<= 1;
}

