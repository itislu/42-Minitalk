/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 02:24:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile char	*;

int	main(int argc, char *argv[])
{
	size_t	len;
	char	*msg;
	pid_t	pid_server;

	parse_input(argc, argv, &msg, &pid_server);
	save_in_static(msg, &send_msg);
	if (!handshake(pid_server))
	{
		if (argc > 2)
		{
			ft_printf("Handshake with server was not successful.\n");
			exit (HANDSHAKE_ERROR);
		}
		else
		{
			ft_printf("No message to transmit.\n");
			exit (ARG_ERROR);
		}
	}
	len = communicate_len(pid_server, msg);
	setup_sigaction(SIG_SERVER_READY, send_msg);
	// Might need sth like this:
	// lensize = send_lentype(len, pid_server);

	wait_for_server(len);
	exit (SUCCESS);
}
