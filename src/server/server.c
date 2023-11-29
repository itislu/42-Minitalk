/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 00:16:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig, siginfo_t *siginfo, void *context);
void	display_msg(int sig, siginfo_t *siginfo);

volatile sig_atomic_t	is_handshake_success[MAX_PID] = {false};

int	main(void)
{
	pid_t				pid_server;
	struct sigaction	sa;

	pid_server = getpid();
	ft_printf("The server PID is: %d\n", pid_server);
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (true)
		pause();
}

void	handle_signal(int sig, siginfo_t *siginfo, void *context)
{
	if (is_handshake_success[siginfo->si_pid] == false)
	{
		if (sig == SIGUSR1)
		{
			kill(siginfo->si_pid, SIGUSR2);
			is_handshake_success[siginfo->si_pid] = true;
		}
	}
	else
	{
		display_msg(sig, siginfo);
	}
}

void	display_msg(int sig, siginfo_t *siginfo)
{
	static unsigned char	c[MAX_PID];
	static int				i[MAX_PID];

	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		if (sig == SIGUSR1)
		{
			c[siginfo->si_pid] += 0b1;
		}
		else if (sig == SIGUSR2)
		{
			c[siginfo->si_pid] += 0b0;
		}
		if (++i[siginfo->si_pid] == 8)
		{
			write(1, &c[siginfo->si_pid], 1);
			c[siginfo->si_pid] = 0;
			i[siginfo->si_pid] = 0;
		}
		else
			c[siginfo->si_pid] <<= 1;
	}
}

// Not used atm
void	reset_sigusr1(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
}
