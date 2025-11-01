/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receiving.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:38:06 by gkhavari          #+#    #+#             */
/*   Updated: 2025/10/17 16:38:08 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_signal_data	g_sig_data = {0, 0, 0, NULL, 0};

static void	reset_signal_data(void)
{
	g_sig_data.len = 0;
	g_sig_data.bit_count = 0;
	g_sig_data.c = 0;
	free(g_sig_data.msg);
	g_sig_data.msg = NULL;
	g_sig_data.active_pid = 0;
}

static void	message_complete(pid_t sender_pid)
{
	if (g_sig_data.msg)
		ft_putstr(g_sig_data.msg);
	kill(sender_pid, SIGUSR1);
	reset_signal_data();
}

void	receive_length(int sig)
{
	int	bit_position;

	if (sig == SIGUSR1)
	{
		bit_position = 31 - g_sig_data.bit_count;
		g_sig_data.len = g_sig_data.len | (1 << bit_position);
	}
	g_sig_data.bit_count++;
	if (g_sig_data.bit_count == 32)
	{
		g_sig_data.msg = (char *)malloc((g_sig_data.len + 1));
		if (!g_sig_data.msg)
			reset_signal_data();
	}
}

void	receive_message(int sig, pid_t sender_pid)
{
	int	bit_position;

	bit_position = 7 - ((g_sig_data.bit_count - 32) % 8);
	if (sig == SIGUSR1)
		g_sig_data.c = g_sig_data.c | (1 << bit_position);
	if (bit_position == 0)
	{
		g_sig_data.msg[(g_sig_data.bit_count - 32) / 8] = g_sig_data.c;
		if (g_sig_data.c == '\0')
		{
			message_complete(sender_pid);
			return ;
		}
		g_sig_data.c = 0;
	}
	g_sig_data.bit_count++;
}
