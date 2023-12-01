/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 18:17:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/01 16:05:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "minitalk.h"

/* Client */
void	wait_until_server_allows_send_msg(void);
void	send_msg(int signo, siginfo_t *info, void *context);
void	transmit_bit(unsigned char *c, int *i, siginfo_t *info);

/* Input check */
int		check_input(int argc, char *argv[]);

/* Handshake */
void	handle_handshake(int signo);
bool	handshake(pid_t pid_server);
void	reset_sigusr1(struct sigaction *sa);

#endif
