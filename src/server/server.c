/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 19:55:35 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

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
	{
		//ft_printf("pausing\n");
		pause();
		//ft_printf("going out of pause\n");
	}
}

void	handle_signal(int sig, siginfo_t *siginfo, void *context)
{
	if (is_handshake_success[siginfo->si_pid] == false)
	{
		if (sig == SIGUSR1)
		{
			is_handshake_success[siginfo->si_pid] = true;
			usleep(100);
			kill(siginfo->si_pid, SIGUSR1);
			ft_printf("handshake successful\n");
			usleep(100);
			kill(siginfo->si_pid, SIGUSR2);
		}
	}
	else
	{
		display_msg(sig, siginfo);
		// usleep(10000);
		kill(siginfo->si_pid, SIGUSR2);
		//ft_printf("sent SIGUSR2\n");
	}
}

void	display_msg(int sig, siginfo_t *siginfo)
{
	static unsigned char	c[MAX_PID];
	static int				i[MAX_PID];
	static	int				bytes;

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
			++bytes;
			// ft_printf("%d\n", bytes);
			c[siginfo->si_pid] = 0;
			i[siginfo->si_pid] = 0;
		}
		else
		{
			c[siginfo->si_pid] <<= 1;
			//ft_printf("received bit #%d\n", i);
		}

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
