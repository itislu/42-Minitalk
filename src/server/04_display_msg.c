/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_display_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:48:10 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 02:16:21 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	display_msg(pid_t client)
{
	ft_printf("%s", g_msg[client]);
	ft_free_and_null((void **) &g_msg[client]);
}
