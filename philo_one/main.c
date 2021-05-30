/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:52:14 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/29 17:49:24 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int mail = 0;

void	ft_init(int argc, char **argv, t_data *data, t_philo *philo)
{
	int i;
	time_now();
	i = 0;
	data->n_philos = ft_atoi(argv[1]);
	if (argc == 6)
		data->max_ph_eat = ft_atoi(argv[5]);
	else
		data->max_ph_eat = -1;
	while (i < data->n_philos)
	{
		philo[i].ph_number = i + 1;
		philo[i].tt_die = ft_atoi(argv[2]);
		philo[i].tt_eat = ft_atoi(argv[3]);
		philo[i].tt_sleep = ft_atoi(argv[4]);
		philo[i].time = time_now();
		philo[i].data = data;
		philo[i].eating_time = 0; 
		philo[i].n_eat = 0;
		philo[i].last_eat = TIMESTAMP;
		philo[i].stat = 0;
		pthread_mutex_init(&(data->f_mutex)[i], NULL);
		pthread_mutex_init(&philo[i].ph_mutex, NULL);
		i++;
	}
	pthread_mutex_init(&data->print_state, NULL);
}

void	ft_print_philo_data(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	printf("%d philosopher on table\n", data->n_philos);
	if (data->max_ph_eat != -1)
		printf("each philosopher should eat max %d times\n", data->max_ph_eat);
	printf("**************\n");
	while (i < data->n_philos)
	{
		printf("%d philo number %d \n", i, philo[i].ph_number);
		printf("----------------\n");
		printf("time_to_die : %d\n", philo[i].tt_die);
		printf("time_to_eat : %d\n", philo[i].tt_eat);
		printf("time_to_sleep : %d\n\n", philo[i].tt_sleep);
		i++;
	}
}

void	ft_clear(t_philo *philo, t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->n_philos)
	{
		pthread_mutex_destroy(&(data->f_mutex)[i]);
		pthread_mutex_destroy(&philo[i].ph_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_state);
	free(philo);
	free(data->thread);
}

void	ft_print_stat(int msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_state);
	if(msg == TAKE_R)
		printf("%ld philo %d take right fork\n", TIMESTAMP, philo->ph_number);
	else if (msg == TAKE_L)
		printf("%ld philo %d take left fork\n",TIMESTAMP, philo->ph_number);
	else if (msg == EATING)
	{
		philo->stat = EATING;
		printf("%ld philo %d eating for the %d th time\n",TIMESTAMP, philo->ph_number, philo->n_eat);
	}
	else if (msg == SLEEPING)
	{
		philo->stat = SLEEPING;
		printf("%ld philo %d sleeping\n",TIMESTAMP, philo->ph_number);
	}
	else if (msg == THINKING)
	{
		philo->stat = THINKING;
		printf("%ld philo %d thinking\n",TIMESTAMP, philo->ph_number);
	}
	else if (msg == DEAD)
	{
		philo->stat = DEAD;
		printf("%ld philo %d died\n",TIMESTAMP, philo->ph_number);
		//pthread_mutex_unlock(&philo->ph_mutex);
		exit(0);
	}
	pthread_mutex_unlock(&philo->data->print_state);
}

void	*ft_routine(void *v_philo)
{
	t_data *data;
	t_philo *philo;
	
	philo = (t_philo *)v_philo;
	//printf(N);
	//mail++;
	data = philo->data;
	//printf("%d\n", philo->ph_number);
	while (1)
	{
		if (philo->n_eat < data->max_ph_eat || data->max_ph_eat == -1)
		{
			pthread_mutex_lock(&(data->f_mutex)[RIGHT]);
			ft_print_stat(TAKE_R ,philo);
			pthread_mutex_lock(&(data->f_mutex)[LEFT]);
			ft_print_stat(TAKE_L ,philo);
			ft_print_stat(EATING ,philo);
			//pthread_mutex_lock(&philo->ph_mutex);
			(philo->n_eat)++;
			usleep(philo->tt_eat * 1000);
			philo->eating_time = time_now();
			pthread_mutex_unlock(&(data->f_mutex)[LEFT]);
			pthread_mutex_unlock(&(data->f_mutex)[RIGHT]);
			//pthread_mutex_unlock(&philo->ph_mutex);
			ft_print_stat(SLEEPING ,philo);
			usleep(philo->tt_sleep * 1000);
			ft_print_stat(THINKING, philo);
			//usleep(60 * 1000);
		}
		else
			return ((void*)0);
	}
	return ((void*)0);
}

void	*ft_cheker(void *v_philo)
{
	t_philo *philo;
	int i;
	unsigned long diff;

	while (1)
	{
		i = 0;
		philo = (t_philo *)v_philo;
		while (i < philo->data->n_philos)
		{
			//printf("++%lu\n", time_now() - philo[i].eating_time);
			diff = time_now() - philo[i].eating_time;
			if (diff > philo[i].tt_die && philo[i].eating_time != 0 && philo[i].stat != EATING)
			{
				//printf("--%lu\n", diff);
				//printf("**%lu\n", time_now() - philo[i].eating_time);
				ft_print_stat(DEAD, &philo[i]);
				//exit (0);
			}
			i++;
		}
		usleep(1000);
	}
}

void	ft_thread(t_philo *philo, t_data *data)
{
	int i;

	i = 0;
	while (i < data->n_philos)
	{
		pthread_create(&data->thread[i], NULL, &ft_routine, &philo[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < data->n_philos)
	{
		pthread_create(&data->thread[i], NULL, &ft_routine, &philo[i]);
		i += 2;
	}
	pthread_create(&data->thread[data->n_philos], NULL, &ft_cheker, philo);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(data->thread[i], NULL);
		//printf("thread %d finish his job\n", i);		
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data		data; 
	t_philo		*philo;

	if (argc == 5 || argc == 6)
	{
		philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
		data.thread = malloc(sizeof(pthread_t) * ft_atoi(argv[1]) + 1);
		data.f_mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
		ft_init(argc, argv, &data, philo);
		ft_thread(philo, &data);
		//ft_print_philo_data(philo, &data);
		ft_clear(philo, &data);
		//printf("%d\n", mail);
	}
	else
		return (arg_count_err());
	return (0);
}
