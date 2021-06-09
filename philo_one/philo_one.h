/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:54:36 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 18:38:00 by hchorfi          ###   ########.fr       */
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

# define TAKE_R 1
# define TAKE_L 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5
# define DEAD 6
# define ONE_DIED 10

typedef struct s_data
{
	int				n_philos;
	int				max_ph_eat;
	pthread_mutex_t	*f_mutex;
	pthread_mutex_t	print_state;
	pthread_t		*thread;
	unsigned long	start_time;
}					t_data;

typedef struct s_philo
{
	int				ph_number;
	int				l_fork;
	int				r_fork;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				n_eat;
	int				stat;
	unsigned long	last_eat;
	unsigned long	eating_time;
	unsigned long	sleeping_time;
	pthread_mutex_t	eat_mutex;
	t_data			*data;
}					t_philo;

/*
** error.c
*/

int					arg_count_err(void);

/*
** utils.c
*/

unsigned long		time_now(void);
int					ft_atoi(const	char *str);
void				ft_clear(t_philo *philo, t_data *data);
int					check_args(int argc, char **argv);

/*
** print.c
*/

int					ft_print_stat(int msg, t_philo *philo);
int					ft_print_stat2(int msg, t_philo *philo);

/*
** init.c
*/

void				ft_init_struct(
						int i, t_philo *philo, t_data *data, char **argv);
void				ft_init(
						int argc, char **argv, t_data *data, t_philo *philo);

#endif
