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

void	handle_signal(int sig)
{
	static unsigned int	c = 0;
	static int	bit_counter = 0;
	static char	*msg = NULL;
	int			bit_position;
	unsigned int	temp;

	if (bit_counter < 32)
	{
		if (sig == SIGUSR1)
		{
			bit_position = 31 - bit_counter;
			temp = 1 << bit_position;
			c = c | temp;
		}
		bit_counter++;
		if (bit_counter == 32)
		{
			msg = (char *)malloc((c + 1) * sizeof(char));
			if (!msg)
				return ;
			c = 0;
		}
	}
	else
	{
		if (sig == SIGUSR1)
		{
			bit_position = (bit_counter - 32) % 8;
			temp = 1 << bit_position;
			c = c | temp;
		}
		bit_counter++;
		bit_position++;
		if (bit_position == 8)
		{
			if (c != '\0')
				msg[bit_position - 32] = c;
			else
			{
				ft_putstr(msg);
				free(msg);
			}
			c = 0;
		}
	}
}

int	main(void)
{
	ft_putstr("Server PID is: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}