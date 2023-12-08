/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_communicate_len.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:02:53 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 02:26:37 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

size_t	communicate_len(pid_t pid_server, char *msg)
{
	size_t	len;
	int		lensize;

	len = ft_strlen(msg);	// What if 0? Mallocing 0 bytes in server is not good.
	save_in_static(len, &send_len);
	setup_sigaction(SIG_SERVER_READY, send_len);
	lensize = send_lentype(len, pid_server);
	wait_for_server(lensize);
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
