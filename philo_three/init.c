/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:43:37 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 15:04:13 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_init_struct(int i, t_philo *philo, t_data *data, char **argv)
{
	philo[i].ph_number = i + 1;
	philo[i].tt_die = ft_atoi(argv[2]);
	philo[i].tt_eat = ft_atoi(argv[3]);
	philo[i].tt_sleep = ft_atoi(argv[4]);
	philo[i].data = data;
	philo[i].eating_time = time_now();
	philo[i].sleeping_time = time_now();
	philo[i].n_eat = 0;
	philo[i].last_eat = time_now();
	philo[i].stat = 0;
	philo[i].l_fork = philo[i].ph_number - 1;
	philo[i].r_fork = ((philo[i].ph_number - 1) + 1) % data->n_philos;
}

void	ft_init(int argc, char **argv, t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->n_philos = ft_atoi(argv[1]);
	if (argc == 6)
		data->max_ph_eat = ft_atoi(argv[5]);
	else
		data->max_ph_eat = -1;
	while (i < data->n_philos)
	{
		ft_init_struct(i, philo, data, argv);
		i++;
	}
	data->pids = malloc(sizeof(pid_t) * data->n_philos);
	sem_unlink(SEMFORKS);
	data->sem_forks = sem_open(SEMFORKS, O_CREAT, 0666, data->n_philos);
	sem_unlink(SEMPRINT);
	data->sem_print = sem_open(SEMPRINT, O_CREAT, 0666, 1);
	sem_unlink(SEMEAT);
	data->sem_print = sem_open(SEMEAT, O_CREAT, 0666, 1);
	data->start_time = time_now();
}
