/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:54:36 by hchorfi           #+#    #+#             */
/*   Updated: 2021/05/29 17:34:29 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

#define LEFT philo->ph_number - 1
#define RIGHT ((philo->ph_number - 1) + 1) % data->n_philos
#define TIMESTAMP time_now() - philo->time
#define TAKE_R 1
#define TAKE_L 2
#define EATING 3
#define SLEEPING 4
#define THINKING 5
#define DEAD 6

typedef struct  s_data
{
    int             n_philos;
    int             max_ph_eat;
    pthread_mutex_t *f_mutex;
    pthread_mutex_t print_state;
    pthread_t	    *thread;
}                   t_data;

typedef struct  s_philo
{
    int         ph_number;
    int         tt_die;
    int         tt_eat;
    int         tt_sleep;
    int         n_eat;
    int         stat;
    unsigned long   last_eat;
    unsigned long   time;
    unsigned long   eating_time;
    pthread_mutex_t ph_mutex;
    t_data      *data;
}               t_philo;

/*
** error.c
*/

int arg_count_err(void);

/*
** utils.c
*/

int	ft_atoi(const char *str);
unsigned long	time_now(void);

#endif
