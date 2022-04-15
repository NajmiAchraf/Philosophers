/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:35:17 by anajmi            #+#    #+#             */
/*   Updated: 2022/04/15 01:45:40 by anajmi           ###   ########.fr       */
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

# define MAXINT	2147483647
# define MININT	-2147483648

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

typedef struct s_data
{
	size_t			nb_philo;
	size_t			tdie;
	size_t			teat;
	size_t			tsleep;
	int				nbr_to_eat;
	pthread_mutex_t	mutex_print;
}				t_data;

typedef struct s_profile
{
	pthread_t		philo;
	pthread_mutex_t	fork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*mutex_print;
	t_data			*data;
	int				nbr_to_eat;
	size_t			id;
	size_t			last_eat;
	size_t			is_die;
}				t_profile;

int		arg_check(int ac, char **av);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

size_t	get_time(void);
size_t	timing(void);
void	msleep(size_t time);

void	printing(t_profile *profile, char *color, char *str);
void	*visor(void *param);
void	*race(void	*param);

#endif
