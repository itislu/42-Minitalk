/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_communicate_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:02:53 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 15:59:05 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

size_t	communicate_len(pid_t server, char *msg)
{
	size_t	len;
	int		lensize;

	if (msg)
		len = ft_strlen(msg) + 1;
	else
		return (0);
	save_in_static((void *) len, &send_len);
	setup_sigaction(SIG_SERVER_READY, send_len);
	lensize = send_lentype(len, server);
	wait_for_server(lensize, MSG_TRANSMISSION_STAGE);
	if (g_stage != MSG_TRANSMISSION_STAGE)
		timeout(server, TIMEOUT_SEC);
	return (len);
}

int	send_lentype(size_t len, pid_t server)
{
	if (len <= UINT_MAX)
	{
		if (kill(server, SIG_UINT) == -1)
			exit(KILL_ERROR);
		return (sizeof(unsigned int));
	}
	else
	{
		if (kill(server, SIG_SIZE_T) == -1)
			exit(KILL_ERROR);
		return (sizeof(size_t));
	}
}

void	send_len(int signo, siginfo_t *info, void *context)
{
	static size_t	len;
	static int		bit;

	(void) context;
	if (!signo && !len)
		len = (size_t) context;
	else if (signo == SIG_SERVER_READY)
		transmit_bit(len, &bit, info->si_pid);
}
