/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/09 13:55:11 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "minitalk.h"

extern volatile char	*g_msg[];

/* Server */
void	handle_signal(int signo, siginfo_t *info, void *context);

/* Server utils */
char	*calloc_msg(size_t len);
void	client_not_reachable(pid_t client, int stage[]);
void	free_all_and_exit(int exit_code);
void	set_bit(volatile char *byte, int signo);

/* 01 Handshake stage */
void	handshake(int signo, pid_t client, int stage[]);

/* 02 Len transmission stage */
int		get_len(size_t *len, int signo, pid_t client);
int		get_lentype(int signo);

/* 03 Msg transmission stage */
int		buffer_msg(size_t *len, int signo, pid_t client);

/* 04 Display msg stage */
void	display_msg(pid_t client);

#endif
