/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 15:16:03 by hchorfi           #+#    #+#             */
/*   Updated: 2021/06/07 20:04:20 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	arg_count_err(void)
{
	printf("Error: please check your argument\n");
	printf("Syntax: ./philo_one number_of_philosophers time_to_die ");
	printf("time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}
