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

static int	error_handler(int pid)
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

int	setup_client(int argc, char **argv, int *server_pid)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putstr("[ERROR] Please enter: ./client <PID> <message>\n");
		return (1);
	}
	*server_pid = ft_atoi(argv[1]);
	if (error_handler(*server_pid))
		return (1);
	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	return (0);
}

void	send_message_loop(int server_pid, char *message)
{
	while (g_ack == 0)
	{
		g_ack = 0;
		ft_putstr("[INFO] Sending message...\n");
		if (send_header(server_pid, message) == -1
			|| send_msg(server_pid, message) == -1)
		{
			ft_putstr("[WARN] Timeout. Retrying...\n");
			g_ack = 0;
		}
		else
		{
			ft_putstr("[SUCCESS] Message delivered successfully!\n");
			break ;
		}
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (setup_client(argc, argv, &server_pid))
		return (1);
	send_message_loop(server_pid, argv[2]);
	return (0);
}
