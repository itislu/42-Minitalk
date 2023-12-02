/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 01:12:46 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile sig_atomic_t	g_is_handshake_success[MAX_PID] = {false};

int	main(void)
{
	pid_t				pid_server;
	struct sigaction	sa;

	pid_server = getpid();
	ft_printf("The server PID is: %d\n", pid_server);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit (SIGEMPTYSET_ERROR);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit (SIGACTION_ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit (SIGACTION_ERROR);
	while (true)
		if (pause() == -1 && errno != EINTR)
			exit (PAUSE_ERROR);
}

void	handle_signal(int signo, siginfo_t *info, void *context)
{
	(void) context;
	if (signo == SIGUSR1 || signo == SIGUSR2)
	{
		if (g_is_handshake_success[info->si_pid] == false)
		{
			if (signo == SIGUSR1)
			{
				handshake(info);
				if (kill(info->si_pid, SIGUSR2) == -1)
					exit (KILL_ERROR);
			}
		}
		else
		{
			if (display_msg(signo, info))
				if (kill(info->si_pid, SIGUSR2) == -1)
					exit (KILL_ERROR);
		}
	}
}

bool	display_msg(int signo, siginfo_t *info)
{
	static unsigned char	c[MAX_PID];
	static int				i[MAX_PID];

	if (signo == SIGUSR1 || signo == SIGUSR2)
	{
		if (signo == SIGUSR1)
			c[info->si_pid] += 0b1;
		else if (signo == SIGUSR2)
			c[info->si_pid] += 0b0;
		if (++i[info->si_pid] == 8)
		{
			write(1, &c[info->si_pid], 1);
			c[info->si_pid] = 0;
			i[info->si_pid] = 0;
		}
		else
			c[info->si_pid] <<= 1;
		return (true);
	}
	else
		return (false);
}
