/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:22 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/29 00:11:10 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <signal.h>

int	main(int argc, char *argv[])
{
	pid_t	pid;
	int		which_arg;

	which_arg = check_input(argc, argv); // To get the opposite: which_arg % 2 + 1
	if (which_arg == -1)
		exit (1);
	pid = ft_atoi(argv[which_arg]);
	if (!handshake(pid))
		exit (2);

}

bool	handshake(pid_t pid)
{
	// Send a certain signal and expect a signal back.
	kill(pid,SIGUSR1);
	// Check if the return signal is SIGUSR2

	// If got the expected return signal, return true, otherwise false.

	//? Does the signal listener need to be terminated now?
}
