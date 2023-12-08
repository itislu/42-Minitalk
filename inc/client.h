/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 12:20:56 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

# define TIMEOUT_SEC	10

extern volatile int	g_stage;

/* Client */
void	wait_for_server(size_t bytes_to_send, int next_stage);
void	transmit_bit(char *c, int *bit, pid_t pid_server);

/* Client utils */
void	save_in_static(void *data, void (*func)(int, siginfo_t *, void *));
void	server_error(int signo, siginfo_t *info, void *context);
void	setup_sigaction(int signal, void (*handler)(int, siginfo_t *, void *));
void	timeout(pid_t pid_server, int timeout_sec);

/* 00 Parse input */
void	parse_input(int argc, char *argv[], char **msg, pid_t *pid_server);
int		check_input(int argc, char *argv[]);
bool	is_valid_pid(char *arg);

/* 01 Handshake */
void	handshake(pid_t pid_server);
void	handle_handshake(int signo, siginfo_t *info, void *context);

/* 02 Communicate len */
size_t	communicate_len(pid_t pid_server, char *msg);
int		send_lentype(size_t len, pid_t pid_server);
void	send_len(int signo, siginfo_t *info, void *context);

/* 03 Send msg */
void	send_msg(int signo, siginfo_t *info, void *context);

#endif
