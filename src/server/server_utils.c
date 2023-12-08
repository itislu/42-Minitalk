/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:16:27 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 15:34:20 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <server.h>

void	free_all_and_exit(int exit_code)
{
	int	i;

	i = 0;
	while (i < MAX_PID)
		ft_free_and_null((void **) &g_msg[i++]);
	exit (exit_code);
}

pid_t	print_pid(void)
{
	static pid_t	pid_server;

	if (!pid_server)
		pid_server = getpid();
	else
		ft_printf("\n");
	ft_printf("The server PID is: %d\n", pid_server);
	return (pid_server);
}

void	set_bit(volatile char *byte, int signo)
{
	if (signo == SIG_ONE)
		*byte |= 0b1;
	else
		*byte &= ~0b1;
}
