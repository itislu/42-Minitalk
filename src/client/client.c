/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/29 16:04:14 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

volatile sig_atomic_t	is_handshake_success = false;

int	main(int argc, char *argv[])
{
	int					arg_msg;
	int					arg_pid;
	pid_t				pid_server;

	arg_pid = check_input(argc, argv); // To get the opposite: arg_pid % 2 + 1
	if (arg_pid == -1)
		exit (1);
	pid_server = ft_atoi(argv[arg_pid]);
	if (!handshake(pid_server))
		exit (2);

	arg_msg = arg_pid % 2 + 1;
	send_msg(pid_server, argv[arg_msg]);
}

void	handle_handshake(int sig)
{
	if (sig == SIGUSR2)
		is_handshake_success = true;
}

void	reset_sigusr2(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR2, sa, NULL);
}

//TODO: Check for failures of all functions
bool	handshake(pid_t pid_server)
{
	struct sigaction	sa;

	sa.sa_handler = handle_handshake;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	// Send a certain signal and expect a signal back.
	kill(pid_server,SIGUSR1);
	// Check if the return signal is SIGUSR2
	sigaction(SIGUSR2, &sa, NULL);
	pause();
	// Reset sigaction
	reset_sigusr2(&sa);
	// If got the expected return signal, return true, otherwise false.
	return (is_handshake_success);

	//? Does the signal listener need to be terminated now?
}
