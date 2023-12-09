/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 15:17:51 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

# define TIMEOUT_SEC	2

enum e_dangerous_pid
{
	NEGATIVE = -2,
	MINUS_ONE = -1,
	ZERO = 0,
	OK = 1
};

extern volatile int	g_stage;

/* Client */
void	wait_for_server(size_t bytes_to_send, int next_stage);
void	transmit_bit(size_t c, int *bit, pid_t server);

/* Client utils */
void	save_in_static(void *data, void (*func)(int, siginfo_t *, void *));
void	msg_received(int signo, siginfo_t *info, void *context);
void	setup_sigaction(int signal, void (*handler)(int, siginfo_t *, void *));
void	timeout(pid_t server, int timeout_sec);

/* 00 Parse input */
void	parse_input(int argc, char *argv[], char **msg, pid_t *server);
int		check_input(int argc, char *argv[]);
bool	is_valid_pid(char *arg, enum e_dangerous_pid *dangerous_pid);
void	check_dangerous_pid(enum e_dangerous_pid dangerous_pid);

/* 01 Handshake stage */
void	handshake(pid_t server);
void	handle_handshake(int signo, siginfo_t *info, void *context);

/* 02 Len transmission stage */
size_t	communicate_len(pid_t server, char *msg);
int		send_lentype(size_t len, pid_t server);
void	send_len(int signo, siginfo_t *info, void *context);

/* 03 Msg transmission stage */
void	send_msg(int signo, siginfo_t *info, void *context);

#endif
