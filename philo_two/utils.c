/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:00:51 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 19:06:53 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

unsigned long	time_now(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int				i;
	int				neg;
	long long int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + str[i++] - '0';
	if (res < 0 && neg > 0)
		return (-1);
	if (res < 0 && neg < 0)
		return (0);
	return (res * neg);
}

void	ft_clear(t_philo *philo, t_data *data)
{
	sem_unlink(SEMFORKS);
	sem_unlink(SEMPRINT);
	sem_unlink(SEMEAT);
	free(data->thread);
	free(philo);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (1);
		}
		if (ft_atoi(argv[i]) >= 0)
			i++;
		else
			return (1);
	}
	return (0);
}
