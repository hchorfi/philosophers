/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:46:39 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 13:24:52 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_print_stat2(int msg, t_philo *philo)
{
	if (msg == SLEEPING)
	{
		philo->stat = SLEEPING;
		printf("\033[0;31m%ld\033[0m ", time_now() - philo->data->start_time);
		printf("\033[0;35mphilo %d sleeping\n\033[0m", philo->ph_number);
	}
	else if (msg == THINKING)
	{
		philo->stat = THINKING;
		printf("\033[0;31m%ld\033[0m ", time_now() - philo->data->start_time);
		printf("\033[0;36mphilo %d thinking\n\033[0m", philo->ph_number);
	}
	else if (msg == DEAD)
	{
		philo->stat = DEAD;
		printf("\033[0;31m%ld\033[0m ", time_now() - philo->data->start_time);
		printf("\033[0;31mphilo %d died\n\033[0m", philo->ph_number);
		exit(1);
	}
}

void	ft_print_stat(int msg, t_philo *philo)
{
	sem_wait(philo->data->sem_print);
	if (msg == TAKE_R)
	{
		printf("\033[0;31m%ld\033[0m ", time_now() - philo->data->start_time);
		printf("\033[0;32mphilo %d take a fork\n\033[0m", philo->ph_number);
	}
	else if (msg == TAKE_L)
	{
		printf("\033[0;31m%ld\033[0m ", time_now() - philo->data->start_time);
		printf("\033[0;32mphilo %d take a fork\n\033[0m", philo->ph_number);
	}
	else if (msg == EATING)
	{
		philo->stat = EATING;
		printf("\033[0;31m%ld\033[0m ", time_now() - philo->data->start_time);
		printf("\033[0;34mphilo %d eating\n\033[0m", philo->ph_number);
	}
	else
		ft_print_stat2(msg, philo);
	sem_post(philo->data->sem_print);
}
