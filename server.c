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
	static unsigned char	c = 0;
	static unsigned int		len = 0;
	static int				bit_count = 0;
	static char				*msg = NULL;
	int						bit_position;

	if (bit_count < 32)
	{
		if (sig == SIGUSR1)
		{
			bit_position = 31 - bit_count;
			len = len | (1 << bit_position);
		}
		bit_count++;
		if (bit_count == 32)
		{
			/*ft_putstr("Message length: ");
			ft_putnbr(len);
			ft_putchar('\n');*/
			msg = (char *)malloc((len + 1) * sizeof(char));
			len = 0;
			if (!msg)
				return ;
		}
	}
	else
	{
		bit_position = 7 - ((bit_count - 32) % 8);
		if (sig == SIGUSR1)
			c = c | (1 << bit_position);
		bit_count++;
		if (bit_position == 0)
		{
			msg[(bit_count - 32) / 8 - 1] = c;
			/*ft_putnbr((bit_count - 32) / 8 - 1);
			ft_putchar('\n');
			ft_putstr("Received: ");
			ft_putchar(c);
			ft_putchar('\n');*/
			if (c == '\0')
			{
				ft_putstr(msg);
				free(msg);
				c = 0;
				len = 0;
				bit_count = 0;
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
