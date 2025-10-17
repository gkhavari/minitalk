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

void	send_bits(int pid, unsigned int data, int bit_count)
{
	int	i;

	i = 0;
	while (i < bit_count)
	{
		if ((data & (1 << (bit_count - 1 - i))) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		wait_for_ack();
		i++;
	}
}

void	send_header(int pid, char *msg)
{
	int	msg_len;

	msg_len = 0;
	while (msg[msg_len])
		msg_len++;
	send_bits(pid, msg_len, sizeof(int) * 8);
}

void	send_msg(int pid, char *msg)
{
	size_t	i;

	i = 0;
	while (msg[i])
	{
		send_bits(pid, msg[i], 8);
		i++;
	}
	send_bits(pid, '\0', sizeof(char) * 8);
}
