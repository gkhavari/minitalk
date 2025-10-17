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

int	g_ack = 0;

static void	handle_ack(int sig)
{
	(void) sig;
	g_ack = 1;
}

void	wait_for_ack(void)
{
	while (!g_ack)
		pause();
	g_ack = 0;
}

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

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putstr("[ERROR] Please enter: ./client <PID> <message>\n");
		return (1);
	}
	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	if (error_handler(server_pid))
		return (1);
	send_header(server_pid, argv[2]);
	send_msg(server_pid, argv[2]);
	return (0);
}
