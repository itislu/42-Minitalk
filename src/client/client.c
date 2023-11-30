/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/30 20:45:30 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

int	check_input(int argc, char *argv[]);
void	send_msg(int sig, siginfo_t *siginfo, void *context);

bool	handshake(pid_t pid_server);
void	handle_handshake(int sig);
void	reset_sigusr1(struct sigaction *sa);

volatile char			*msg;

int	main(int argc, char *argv[])
{
	int					arg_msg;
	int					arg_pid;
	pid_t				pid_server;
	struct sigaction	sa;

	arg_pid = check_input(argc, argv);
	if (arg_pid == -1)
		exit (1);
	arg_msg = arg_pid % 2 + 1;
	msg = argv[arg_msg];

	pid_server = ft_atoi(argv[arg_pid]);
	if (!handshake(pid_server))
		exit (2);

	sa.sa_sigaction = send_msg;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	while (true)
	{
		pause();
	}
}

//TODO: Check for failures of all functions
bool	handshake(pid_t pid_server)
{
	struct sigaction	sa;

	sa.sa_handler = handle_handshake;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	// Send a certain signal and expect a signal back.
	sigaction(SIGUSR1, &sa, NULL);

	kill(pid_server, SIGUSR1);
	// Check if the return signal is SIGUSR1
	pause();
	reset_sigusr1(&sa);
	// If got the expected return signal, return true, otherwise false.
	return (msg);

	//? Does the signal listener need to be terminated now?
}

void	handle_handshake(int sig)
{
	if (sig != SIGUSR1)
		msg = NULL;
}

void	reset_sigusr1(struct sigaction *sa)
{
	sa->sa_handler = SIG_DFL;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
}

void	send_msg(int sig, siginfo_t *siginfo, void *context)
{
	static unsigned char	c;
	static int				i;

	if (i == 8)
	{
		msg++;
		i = 0;
	}
	if (msg && *msg)
	{
		if (i == 0)
			c = *msg;
		ft_printf("send_msg_#%d:", i);
		ft_printf("|%s|\n", msg);
		// if (i == 7)
		// 	msg++;
		if (c & 0b10000000)
		{
			kill(siginfo->si_pid, SIGUSR1);
			display_msg_test(1);
		}
		else
		{
			kill(siginfo->si_pid, SIGUSR2);
			display_msg_test(0);
		}
		c <<= 1;
		i++;
	}
	else
		exit (0);
}
