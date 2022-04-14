/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:35:17 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/13 22:55:38 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <strings.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define C_CYAN "\033[1;36m"
# define C_BLUE "\033[1;34m"
# define C_GREEN "\033[1;32m"
# define C_YELOW "\033[1;33m"
# define C_RED "\033[1;31m"

# define TFORK "has taken a fork"
# define ISEAT "is eating"
# define ISLEP "is sleeping"
# define ISTHI "is thinking"
# define DIE "died"
/*
number_of_philosophers
time_to_die
time_to_eat
time_to_sleep 
[number_of_times_each_philosopher_must_eat]
*/
int	ft_atoi(const char *str);
typedef struct s_data
{
	size_t			nb_philo;
	size_t			tdie;
	size_t			teat;
	size_t			tsleep;
	size_t			nb_teat;
}				t_data;

typedef struct s_profile
{
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	t_data			*data;
	size_t			id;
	size_t			last_eat;
}				t_profile;

#endif