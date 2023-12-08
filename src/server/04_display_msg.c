/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_display_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:48:10 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 15:48:55 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	display_msg(volatile char **msg)
{
	ft_printf("%s", *msg);
	ft_free_and_null((void **) msg);
	sleep(1);
	print_pid();
}
