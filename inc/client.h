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

extern volatile char	*;

/* Client utils */
void	save_in_static(void *data, void (*func)(int, siginfo_t *, void *));
void	server_error(int signo, siginfo_t *info, void *context);
void	setup_sigaction(int signal, void (*handler)(int, siginfo_t *, void *));
void	transmit_bit(size_t *c, int *bit, pid_t pid);
void	wait_for_server(size_t bytes_to_send);

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
