/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:44:19 by gkhavari          #+#    #+#             */
/*   Updated: 2025/10/08 15:44:22 by gkhavari         ###   ########.fr       */
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
		usleep(100); // Add delay between signals (100us)
		i++;
	}
}

int	error_handler(int pid)
{
	if (pid == -1)
	{
		ft_putstr("[ERROR] Please don't try to log me out...\n");
		return (1);
	}
	if (kill(pid, 0) != 0)
	{
		ft_putstr("[ERROR] Please enter: a valid PID\n");
		return (1);
	}
	return (0);
}

void	send_header(int pid, char *msg)
{
	int	msg_len;

	msg_len = 0;
//	send_bits(pid, 1, 8);
	while (msg[msg_len])
		msg_len++;
	send_bits(pid, msg_len, 32);
}

void	send_msg(int pid, char *msg)
{
	size_t	i;

	i = 0;
//	send_bits(pid, 2, 8);
	while (msg[i])
	{
		send_bits(pid, msg[i], 8);
		i++;
	}
	send_bits(pid, '\0', 8);
}

int	main(int argc, char **argv)
{
	int		server_pid;

	if (argc != 3)
	{
		ft_putstr("[ERROR] Please enter: ./client <PID> <message>\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (error_handler(server_pid))
		return (1);
	send_header(server_pid, argv[2]);
	send_msg(server_pid, argv[2]);
	return (0);
}
