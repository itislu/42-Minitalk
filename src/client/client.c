/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 23:17:29 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile char	*g_msg;

int	main(int argc, char *argv[])
{
	int					argno_msg;
	int					argno_pid;
	pid_t				pid_server;

	argno_pid = check_input(argc, argv);
	if (argno_pid == -1)
		exit (ARG_ERROR);
	argno_msg = argno_pid % 2 + 1;
	g_msg = argv[argno_msg];
	pid_server = ft_atoi(argv[argno_pid]);
	if (!handshake(pid_server))
		exit (HANDSHAKE_ERROR);
	wait_until_server_allows_send_msg();
}

void	wait_until_server_allows_send_msg(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = send_msg;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit (SIGEMPTYSET_ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (SIGACTION_ERROR);
	while (true)
		if (pause() == -1 && errno != EINTR)
			exit (PAUSE_ERROR);
}

void	send_msg(int signo, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				i;

	if (i == 8)
	{
		g_msg++;
		i = 0;
	}
	if (g_msg && *g_msg)
	{
		if (i == 0)
			c = *g_msg;
		if (c & 0b10000000)
		{
			if (kill(info->si_pid, SIGUSR1) == -1)
				exit (KILL_ERROR);
		}
		else
			if (kill(info->si_pid, SIGUSR2) == -1)
				exit (KILL_ERROR);
		c <<= 1;
		i++;
	}
	else
		exit (SUCCESS);
}
