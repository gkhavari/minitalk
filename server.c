/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:44:02 by gkhavari          #+#    #+#             */
/*   Updated: 2025/10/08 15:44:13 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	pid_t	sender_pid;

	sender_pid = info->si_pid;
	(void)context;
	if (g_sig_data.active_pid == 0)
		g_sig_data.active_pid = sender_pid;
	if (sender_pid != g_sig_data.active_pid)
		return ;
	if (sender_pid == g_sig_data.active_pid)
	{
		if (g_sig_data.bit_count < 32)
			receive_length(sig);
		else
			receive_message(sig, sender_pid);
		kill(sender_pid, SIGUSR2);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr("Server PID is: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
