/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:53:46 by gkhavari          #+#    #+#             */
/*   Updated: 2025/10/13 15:53:49 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define TIMEOUT_STEPS 10000
# define STEP_USEC 100

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_signal_data
{
	unsigned int	len;
	int				bit_count;
	unsigned char	c;
	char			*msg;
	pid_t			active_pid;
}	t_signal_data;

extern t_signal_data	g_sig_data;
extern int				g_ack;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
int		ft_atoi(const char *str);
void	receive_length(int sig);
void	receive_message(int sig, pid_t sender_pid);
void	handle_ack(int sig);
int		send_header(int pid, char *msg);
int		send_msg(int pid, char *msg);

#endif
