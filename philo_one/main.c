/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:52:14 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 18:21:02 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mutex);
	ft_print_stat(EATING, philo);
	philo->eating_time = time_now();
	usleep((philo->tt_eat - 20) * 1000);
	(philo->n_eat)++;
	while ((time_now() - philo->eating_time) < ((unsigned long)philo->tt_eat))
		;
	pthread_mutex_unlock(&philo->eat_mutex);
}

void	*ft_routine(void *v_philo)
{
	t_data	*data;
	t_philo	*philo;

	philo = (t_philo *)v_philo;
	data = philo->data;
	while (1)
	{
		if (philo->n_eat < data->max_ph_eat || !data->max_ph_eat
			|| data->max_ph_eat == -1)
		{
			pthread_mutex_lock(&(data->f_mutex)[philo->r_fork]);
			ft_print_stat(TAKE_R, philo);
			pthread_mutex_lock(&(data->f_mutex)[philo->l_fork]);
			ft_print_stat(TAKE_L, philo);
			ft_eat(philo);
			pthread_mutex_unlock(&(data->f_mutex)[philo->r_fork]);
			pthread_mutex_unlock(&(data->f_mutex)[philo->l_fork]);
			ft_print_stat(SLEEPING, philo);
			usleep(philo->tt_sleep * 1000);
			ft_print_stat(THINKING, philo);
		}
		else
			return ((void *)0);
	}
	return ((void *)0);
}

int	ft_cheker(void *v_philo)
{
	t_philo			*philo;
	int				i;
	unsigned long	diff;

	philo = (t_philo *)v_philo;
	while (1)
	{
		i = 0;
		while (i < philo->data->n_philos)
		{
			diff = time_now() - philo[i].eating_time;
			if (diff > philo[i].tt_die && philo[i].n_eat
				!= philo[i].data->max_ph_eat && philo[i].stat != EATING)
			{
				pthread_mutex_lock(&philo[i].eat_mutex);
				ft_print_stat(DEAD, &philo[i]);
				return (ONE_DIED);
			}
			i++;
		}
		if (philo[i - 1].n_eat == philo[i - 1].data->max_ph_eat - 1)
			break ;
		usleep(100);
	}
	return (0);
}

int	ft_thread(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&data->thread[i], NULL, &ft_routine, &philo[i]);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < data->n_philos)
	{
		pthread_create(&data->thread[i], NULL, &ft_routine, &philo[i]);
		i += 2;
	}
	i = 0;
	if (ft_cheker(philo) != ONE_DIED)
	{
		while (i < data->n_philos)
		{
			pthread_join(data->thread[i], NULL);
			i++;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (argc == 5 || argc == 6)
	{
		if (check_args(argc, argv))
			return (arg_count_err());
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		data.thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
		data.f_mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		ft_init(argc, argv, &data, philo);
		ft_thread(philo, &data);
		ft_clear(philo, &data);
	}
	else
		return (arg_count_err());
	return (0);
}
