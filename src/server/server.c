/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:39:25 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 16:59:12 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

volatile char	*g_msg[MAX_PID];

int	main(void)
{
	pid_t				pid_server;
	struct sigaction	sa;

	pid_server = print_pid();
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
	if (stage[info->si_pid] == HANDSHAKE_STAGE)
		return (handshake(signo, info->si_pid, stage));
	else if (stage[info->si_pid] == TRANSMIT_LEN_STAGE)
	{
		stage[info->si_pid] = get_len(&len[info->si_pid], signo, info->si_pid);
	}
	else if (stage[info->si_pid] == TRANSMIT_MSG_STAGE)
	{
		stage[info->si_pid] = buffer_msg(&len[info->si_pid], signo, info->si_pid);
		if (stage[info->si_pid] == DISPLAY_MSG_STAGE)
		{
			display_msg(&g_msg[info->si_pid]);
			stage[info->si_pid] = HANDSHAKE_STAGE;
		}
	}
	if (kill(info->si_pid, SIG_SERVER_READY) == -1)
		free_all_and_exit(KILL_ERROR);
}
