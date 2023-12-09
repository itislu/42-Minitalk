/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 16:41:57 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile int	g_stage = HANDSHAKE_STAGE;

int	main(int argc, char *argv[])
{
	size_t	len;
	char	*msg;
	pid_t	pid_server;

	parse_input(argc, argv, &msg, &pid_server);
	save_in_static(msg, &send_msg);
	handshake(pid_server);
	if (g_stage != TRANSMIT_LEN_STAGE)
	{
		ft_printf("Handshake with server was not successful.\n");
		exit (HANDSHAKE_ERROR);
	}
	len = communicate_len(pid_server, msg);
	if (len == 0)
	{
		ft_printf("No message to transmit.\n");
		exit (ARG_ERROR);
	}
	setup_sigaction(SIG_SERVER_READY, send_msg);
	wait_for_server(len, DISPLAY_MSG_STAGE);
	sleep(TIMEOUT_SEC);
	if (g_stage != DISPLAY_MSG_STAGE)
		timeout(server, TIMEOUT_SEC);
	else
		exit (SUCCESS);
}

void	wait_for_server(size_t bytes_to_send, int next_stage)
{
	size_t	bytes_sent;
	int		bits_sent;

	bytes_sent = 0;
	while (bytes_sent < bytes_to_send)
	{
		bits_sent = 0;
		while (bits_sent < 8)
		{
			if (sleep(TIMEOUT_SEC) == 0)
				return ;
			bits_sent++;
		}
		bytes_sent++;
	}
	g_stage = next_stage;
}

void	transmit_bit(size_t *c, int *bit, pid_t pid_server)
{
	static size_t	mask;

	if (*bit == 0)
		mask = 0b1;
	if (*c & mask)
	{
		if (kill(pid_server, SIG_ONE) == -1)
			exit (KILL_ERROR);
	}
	else
		if (kill(pid_server, SIG_ZERO) == -1)
			exit (KILL_ERROR);
	mask <<= 1;
	(*bit)++;
}
