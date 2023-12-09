/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_communicate_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:02:53 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 16:08:49 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

size_t	communicate_len(pid_t pid_server, char *msg)
{
	size_t	len;
	int		lensize;

	len = ft_strlen(msg);
	if (len == 0)
		return (len);
	save_in_static((void *) len, &send_len);
	setup_sigaction(SIG_SERVER_READY, send_len);
	lensize = send_lentype(len, pid_server);
	wait_for_server(lensize, TRANSMIT_MSG_STAGE);
	if (g_stage != TRANSMIT_MSG_STAGE)
		timeout(pid_server, TIMEOUT_SEC);
	return (len);
}

int	send_lentype(size_t len, pid_t pid_server)
{
	if (len <= UINT_MAX)
	{
		if (kill(pid_server, SIG_INT) == -1)
			exit(KILL_ERROR);
		return (sizeof(unsigned int));
	}
	else
	{
		if (kill(pid_server, SIG_LONG) == -1)
			exit(KILL_ERROR);
		return (sizeof(size_t));
	}
}

void	send_len(int signo, siginfo_t *info, void *context)
{
	static size_t	len;
	static int		i;

	(void) context;
	(void) info;
	if (!signo && !len)
		len = (size_t) context;
	else if (signo == SIG_SERVER_READY)
		transmit_bit(&len, &i, info->si_pid);
}
