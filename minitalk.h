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

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

typedef struct s_signal_data
{
	unsigned int	len;
	int				bit_count;
	unsigned char	c;
	char			*msg;
}	t_signal_data;

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int n);
int		ft_atoi(const char *str);
void	send_header(int pid, char *msg);
void	send_msg(int pid, char *msg);
void	wait_for_ack(void);
void	handle_signal(int sig, siginfo_t *info, void *context);

#endif
