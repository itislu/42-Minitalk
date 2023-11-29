/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/29 17:24:01 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	is_handshake_success[MAX_PID] = {false};

int	main(void)
{
	pid_t				pid_server;
	struct sigaction	sa;

	pid_server = getpid();
	ft_printf("The server PID is: %d", pid_server);
	sa.sa_sigaction = handle_handshake;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL);
	pause();

	reset_sigusr1(&sa);

	
}

void	handle_handshake(int sig, siginfo_t *siginfo, void *context)
{
	if (sig == SIGUSR1)
	{
		kill(siginfo->si_pid, SIGUSR2);
		is_handshake_success[siginfo->si_pid] = true;
	}
}

void	reset_sigusr1(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
}
