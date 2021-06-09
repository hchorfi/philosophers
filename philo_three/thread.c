/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 19:31:36 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 19:39:27 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_thread2(t_philo *philo, t_data *data)
{
	int	i;
	int	j;
	int	stat;

	i = 0;
	while (i < data->n_philos)
	{
		waitpid(-1, &stat, 0);
		if (WIFEXITED(stat))
		{
			if (WEXITSTATUS(stat) == 1)
			{
				j = 0;
				while (j < data->n_philos)
				{
					kill(data->pids[j], SIGINT);
					j++;
				}
				exit(1);
			}
		}
		i++;
	}
}

void	ft_thread_odd(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		data->pids[i] = fork();
		if (!data->pids[i])
		{
			pthread_create(&data->thread[i], NULL, &ft_routine, &philo[i]);
			ft_cheker(&philo[i]);
			exit(0);
		}
		i += 2;
	}	
}

void	ft_thread(t_philo *philo, t_data *data)
{
	int	i;

	i = 1;
	ft_thread_odd(philo, data);
	usleep(100);
	while (i < data->n_philos)
	{
		data->pids[i] = fork();
		if (!data->pids[i])
		{
			pthread_create(&data->thread[i], NULL, &ft_routine, &philo[i]);
			ft_cheker(&philo[i]);
			exit(0);
		}
		i += 2;
	}
	ft_thread2(philo, data);
}
