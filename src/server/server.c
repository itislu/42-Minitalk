/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 15:41:44 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile char	*g_msg[MAX_PID];

int	main(void)
{
	struct sigaction	sa;

	ft_printf("The server PID is: %d\n", getpid());
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
		free_all_and_exit(SIGEMPTYSET_ERROR);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		free_all_and_exit(SIGACTION_ERROR);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		free_all_and_exit(SIGACTION_ERROR);
	while (true)
		if (pause() == -1 && errno != EINTR)
			free_all_and_exit(PAUSE_ERROR);
}

void	handle_signal(int signo, siginfo_t *info, void *context)
{
	static int		stage[MAX_PID];
	static size_t	len[MAX_PID];

	(void) context;
	if (stage[CLIENT] == HANDSHAKE_STAGE)
	{
		return (handshake(signo, CLIENT, stage));
	}
	else if (stage[CLIENT] == LEN_TRANSMISSION_STAGE)
	{
		stage[CLIENT] = get_len(&len[CLIENT], signo, CLIENT);
	}
	else if (stage[CLIENT] == MSG_TRANSMISSION_STAGE)
	{
		stage[CLIENT] = buffer_msg(&len[CLIENT],
				signo, CLIENT);
	}
	if (stage[CLIENT] == DISPLAY_MSG_STAGE)
	{
		display_msg(CLIENT);
		stage[CLIENT] = HANDSHAKE_STAGE;
		kill(CLIENT, SIG_MSG_RECEIVED);
	}
	else if (kill(CLIENT, SIG_SERVER_READY) == -1)
		client_not_reachable(CLIENT, stage);
}
