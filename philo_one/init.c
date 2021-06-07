/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:43:37 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/06 17:59:28 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
		pthread_mutex_init(&(data->f_mutex)[i], NULL);
		pthread_mutex_init(&philo[i].eat_mutex, NULL);
		i++;
	}
	data->start_time = time_now();
	pthread_mutex_init(&data->print_state, NULL);
}
