/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sending.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:17:47 by gkhavari          #+#    #+#             */
/*   Updated: 2025/10/17 15:17:50 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_ack = 0;

void	handle_ack(int sig)
{
	if (sig == SIGUSR2)
		g_ack = 1;
	if (sig == SIGUSR1)
		g_ack = 2;
}

int	wait_for_ack(void)
{
	int	counter;
	int	ack;

	counter = 0;
	while (!g_ack)
	{
		usleep(STEP_USEC);
		counter++;
		if (counter >= TIMEOUT_STEPS)
			return (-1);
	}
	ack = g_ack;
	g_ack = 0;
	return (ack);
}

static int	send_bits(int pid, unsigned int data, int bit_count)
{
	int	i;
	int	ack;

	i = 0;
	while (i < bit_count)
	{
		if ((data & (1 << (bit_count - 1 - i))) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		ack = wait_for_ack();
		if (ack == -1)
			return (ack);
		i++;
	}
	return (ack);
}

int	send_header(int pid, char *msg)
{
	int	msg_len;

	msg_len = 0;
	while (msg[msg_len])
		msg_len++;
	return (send_bits(pid, msg_len, sizeof(int) * 8));
}

int	send_msg(int pid, char *msg)
{
	size_t	i;
	int		result;

	i = 0;
	while (msg[i])
	{
		result = send_bits(pid, msg[i], 8);
		if (result == -1)
			return (result);
		i++;
	}
	return (send_bits(pid, '\0', sizeof(char) * 8));
}
