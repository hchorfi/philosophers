/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:52:14 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 19:32:11 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->data->sem_eat);
	ft_print_stat(EATING, philo);
	philo->eating_time = time_now();
	usleep((philo->tt_eat - 20) * 1000);
	(philo->n_eat)++;
	while ((time_now() - philo->eating_time) < ((unsigned long)philo->tt_eat))
		;
	sem_post(philo->data->sem_eat);
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
			sem_wait(data->sem_forks);
			ft_print_stat(TAKE_R, philo);
			sem_wait(data->sem_forks);
			ft_print_stat(TAKE_L, philo);
			ft_eat(philo);
			sem_post(data->sem_forks);
			sem_post(data->sem_forks);
			ft_print_stat(SLEEPING, philo);
			usleep(philo->tt_sleep * 1000);
			ft_print_stat(THINKING, philo);
		}
		else
			exit(0);
	}
	return (NULL);
}

void	*ft_cheker(t_philo *philo)
{
	int				i;
	unsigned long	diff;

	while (1)
	{
		diff = time_now() - philo->eating_time;
		if (diff > philo->tt_die && philo->n_eat
			!= philo->data->max_ph_eat && philo->stat != EATING)
		{
			sem_wait(philo->data->sem_eat);
			ft_print_stat(DEAD, philo);
		}
		usleep(100);
	}
	return ((void *)0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	int			i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		if (check_args(argc, argv))
			return (arg_count_err());
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		data.thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
		ft_init(argc, argv, &data, philo);
		ft_thread(philo, &data);
		ft_clear(philo, &data);
	}
	else
		return (arg_count_err());
	return (0);
}
