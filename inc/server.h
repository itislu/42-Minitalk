/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/08 16:44:50 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

extern volatile char	*g_msg[];

/* Server */
void	handle_signal(int signo, siginfo_t *info, void *context);

/* Server utils */
void	free_all_and_exit(int exit_code);
pid_t	print_pid(void);
void	set_bit(volatile char *byte, int signo);

/* 01 Handshake stage */
void	handshake(int signo, pid_t pid_client, int stage[]);

/* 02 Transmit len stage */
int		get_len(size_t *len, int signo, pid_t pid_client);
int		get_lentype(int signo);

/* 03 Transmit msg stage */
int		buffer_msg(size_t *len, int signo, pid_t pid_client);

/* 04 Display msg stage */
void	display_msg(volatile char **msg);

#endif
