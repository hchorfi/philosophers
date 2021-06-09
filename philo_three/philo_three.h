/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 14:54:36 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/08 19:34:11 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <signal.h>
# include <semaphore.h>

# define TAKE_R 1
# define TAKE_L 2
# define EATING 3
# define SLEEPING 4
# define THINKING 5
# define DEAD 6
# define SEMFORKS "semaphore_forks"
# define SEMPRINT "semaphore_print"
# define SEMEAT "semaphore_eat"

typedef struct s_data
{
	int				n_philos;
	int				max_ph_eat;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_eat;
	pthread_t		*thread;
	pid_t			*pids;
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

void				ft_print_stat(int msg, t_philo *philo);
void				ft_print_stat2(int msg, t_philo *philo);

/*
** thread.c
*/

void				ft_thread2(t_philo *philo, t_data *data);
void				ft_thread_odd(t_philo *philo, t_data *data);
void				ft_thread(t_philo *philo, t_data *data);

/*
** init.c
*/

void				ft_init_struct(
						int i, t_philo *philo, t_data *data, char **argv);
void				ft_init(
						int argc, char **argv, t_data *data, t_philo *philo);
void				*ft_routine(void *v_philo);
void				*ft_cheker(t_philo *philo);

#endif
